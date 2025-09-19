import os

# Constants for maximum allocated sizes
IMAGE1_MAX_SIZE = 1364 * 1024  # 850 KB + 64kb bootloader
IMAGE2_MAX_SIZE = 508 * 1024   # 350 KB

def pad_with_ff(data: bytes, final_size: int) -> bytes:
    """Pad the input data with 0xFF to reach the final_size."""
    if len(data) > final_size:
        raise ValueError(f"Data size ({len(data)} bytes) exceeds allowed limit ({final_size} bytes)")
    return data + b'\xFF' * (final_size - len(data))

def combine_images(image1_file, image2_file, output_file):
    with open(image1_file, 'rb') as f:
        img1 = f.read()
    with open(image2_file, 'rb') as f:
        img2 = f.read()

    print(f"Image 1 size: {len(img1)} bytes")
    print(f"Image 2 size: {len(img2)} bytes")

    # Pad both images
    padded_img1 = pad_with_ff(img1, IMAGE1_MAX_SIZE)
    padded_img2 = pad_with_ff(img2, IMAGE2_MAX_SIZE)

    # Combine and write
    with open(output_file, 'wb') as out:
        out.write(padded_img1 + padded_img2)

    print(f"Combined image saved as '{output_file}' (Size: {len(padded_img1) + len(padded_img2)} bytes)")

# File names (must be in the same directory)
os.getcwd()
print(os.getcwd())
os.chdir("..")
os.getcwd()
print(os.getcwd())
#'sdk-ameba-v7.1d','project','realtek_amebaz2_v0_example','GCC-RELEASE','application_is','Debug','bin'
flash_is_bin=os.path.join(os.getcwd(),'sdk-ameba-v7.1d','project','realtek_amebaz2_v0_example','GCC-RELEASE','application_is','Debug','bin','flash_is.bin')
reneses_bin=os.path.join(os.getcwd(),'sdk-ameba-v7.1d','Hoags','reneses.bin')
HE3_reneses_flash_is_bin=os.path.join(os.getcwd(),'sdk-ameba-v7.1d','project','realtek_amebaz2_v0_example','GCC-RELEASE','application_is','Debug','bin','HE3_reneses_flash_is.bin')
os.chdir("HE3_final")
combine_images(flash_is_bin, reneses_bin, 'HE3_reneses_flash_is.bin')
