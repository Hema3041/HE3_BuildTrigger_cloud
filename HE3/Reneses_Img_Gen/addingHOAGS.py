import os 
def calculate_checksum(record):
    """ Calculate checksum for an S-record """
    byte_values = [int(record[i:i+2], 16) for i in range(2, len(record), 2)]
    checksum = (sum(byte_values) & 0xFF) ^ 0xFF
    return f"{checksum:02X}"

def create_srecord(record_type, address, data):
    """ Create an S2 record with proper checksum """
    address_bytes = f"{address:06X}"  # 24-bit address for S2
    byte_count = len(data) + 4  # Byte count = Address (3 bytes) + Data + Checksum (1 byte)
    data_bytes = ''.join(f"{byte:02X}" for byte in data)
    base_record = f"S{record_type}{byte_count:02X}{address_bytes}{data_bytes}"
    checksum = calculate_checksum(base_record)
    return base_record + checksum

def find_last_address(s_records):
    """ Find the highest data address from S2 records """
    s2_addresses = [int(record[4:10], 16) for record in s_records if record.startswith("S2")]

    if not s2_addresses:
        raise ValueError("No valid S2 records found.")

    return max(s2_addresses)

def insert_srecords(s_records):
    """ Insert new S2 records before the last S8/S7/S9 record """
    last_address = find_last_address(s_records)

    # Align new records properly
    new_address_1 = last_address + 0x10  # First new record
    new_address_2 = new_address_1 + 4    # Second record right after

    new_records = [
        create_srecord("2", new_address_1, [0x00, 0x00, 0x00, 0x00]),
        create_srecord("2", new_address_2, [0x48, 0x4F, 0x41, 0x47, 0x53])  # "HOAGS"
    ]

    updated_records = []
    for record in s_records:
        if record.startswith("S8") or record.startswith("S7") or record.startswith("S9"):
            updated_records.extend(new_records)  # Insert before end record
        updated_records.append(record)

    return updated_records

# Read input S-record file
for filename in os.listdir("."):
    if filename.startswith("RAseries") and filename.endswith(".srec"):
        with open(filename, "r") as file:
            original_srecords = [line.strip() for line in file.readlines()]
            print(f"Processed file: {filename}")
            # You can process `original_srecords` here as needed


# Insert the new records before the last S8/S7/S9 record
final_srecords = insert_srecords(original_srecords)

# Write output S-record file
with open("output.srec", "w") as file:
    file.write("\n".join(final_srecords) + "\n")
