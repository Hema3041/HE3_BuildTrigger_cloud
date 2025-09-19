import boto3
from botocore.exceptions import NoCredentialsError, ClientError
import argparse

# ====== Configuration ======
local_file = "final_he3_reneses.bin"  # Path to your .bin file
bucket_name = "hoags-mp-release"
s3_path = "Livpure/Automation_build/final_he3_reneses.bin"  # Path in S3
region_name = "ap-south-1"  # Replace with your bucket's region

# ====== Upload function ======
def upload_to_s3(local_file, bucket_name, s3_path, access_key, secret_key, region_name):
    try:
        s3_client = boto3.client(
            's3',
            aws_access_key_id=access_key,
            aws_secret_access_key=secret_key,
            region_name=region_name
        )

        s3_client.upload_file(local_file, bucket_name, s3_path)
        print(f"File uploaded successfully to s3://{bucket_name}/{s3_path}")
    except FileNotFoundError:
        print(f"The file {local_file} was not found.")
    except NoCredentialsError:
        print("AWS credentials not available or incorrect.")
    except ClientError as e:
        print("Error uploading file:", e)

# ====== Run upload with credentials as arguments ======
parser = argparse.ArgumentParser(description="Upload a .bin file to S3")

parser.add_argument("--access_key", required=True, help="AWS Access Key")
parser.add_argument("--secret_key", required=True, help="AWS Secret Key")
args = parser.parse_args()


upload_to_s3(local_file, bucket_name, s3_path, args.access_key, args.secret_key, region_name)
