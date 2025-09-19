import struct
import xml.etree.ElementTree as ET

INPUT_BINARY = 'HE3_reneses_firmware_is.bin'
OUTPUT_BINARY = 'final_he3_reneses.bin'
XML_FILE = 'metadata.xml'

def pad_to_32bit(data: bytes) -> bytes:
    """Pad data to a multiple of 4 bytes with zero bytes."""
    pad_len = (4 - (len(data) % 4)) % 4
    return data + b'\x00' * pad_len

def compute_checksum(data: bytes) -> int:
    """Compute a 32-bit checksum over the input bytes."""
    data = pad_to_32bit(data)
    checksum = 0
    for i in range(0, len(data), 4):
        word, = struct.unpack('>I', data[i:i+4])
        checksum = (checksum + word) & 0xFFFFFFFF
    return (-checksum) & 0xFFFFFFFF

def parse_metadata(xml_file: str) -> list:
    """Parse the XML file to extract tag number and value."""
    tree = ET.parse(xml_file)
    root = tree.getroot()
    tag_value_list = []

    for tag in root.findall('tag'):
        tagname = tag.find('tagname').text.strip()
        tagno = int(tag.find('tagno').text.strip())
        value = tag.find('value').text.strip().encode('utf-8')
        print(f"Parsed Tag - Name: {tagname}, Tag No: {tagno}, Value: {value}")
        tag_value_list.append((tagno, value))

    return tag_value_list

def build_tlv_block(tag_value_list: list) -> bytes:
    """Build TLV blocks from parsed tag-value pairs."""
    tlv_data = b''
    for tagno, value in tag_value_list:
        tag_bytes = struct.pack('>I', tagno)
        length_bytes = struct.pack('>I', len(value))
        tlv_entry = tag_bytes + length_bytes + value
        tlv_data += pad_to_32bit(tlv_entry)
    return tlv_data

def process_binary_image(input_file: str, output_file: str, xml_file: str):
    # Step 1: Read original binary file
    with open(input_file, 'rb') as f:
        firmware_data = pad_to_32bit(f.read())

    # Step 2: Parse XML for tag-value pairs
    tag_value_list = parse_metadata(xml_file)
    tlv_block = build_tlv_block(tag_value_list)

    # Step 3: Offset (where TLV starts)
    offset_length = len(firmware_data)
    offset_bytes = struct.pack('>I', offset_length)

    # Step 4: Combine firmware + TLV + offset
    final_data = firmware_data + tlv_block + offset_bytes

    # Step 5: Append checksum
    checksum = compute_checksum(final_data)
    checksum_bytes = struct.pack('>I', checksum)
    final_data += checksum_bytes

    # Info
    print(f"\nTLV starts at offset: {offset_length} bytes")
    print(f"Checksum: 0x{checksum:08X}")
    print(f"Checksum valid: {compute_checksum(final_data) == 0}")

    # Step 6: Write final binary
    with open(output_file, 'wb') as f:
        f.write(final_data)
    print(f"Final firmware written to: {output_file}")

def verify_checksum(filename: str) -> bool:
    """Verify the checksum of the binary file."""
    with open(filename, 'rb') as f:
        data = f.read()
    return compute_checksum(data) == 0

if __name__ == '__main__':
    process_binary_image(INPUT_BINARY, OUTPUT_BINARY, XML_FILE)
    print("Final checksum valid:", verify_checksum(OUTPUT_BINARY))
