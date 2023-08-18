#!/usr/bin/env python3

import functools
import os
import hashlib
import subprocess
import json
import re
import shutil
import sys
import gzip


PROCESS_ENC = "mbcs" if sys.platform.startswith("win") else "utf-8"

def prepare_data_files(source=None, target=None, env=None, base="."):
    data_source_dir = os.path.join(base, "data")
    data_dir = env.get("PROJECT_DATA_DIR", env.get("PROJECTDATA_DIR"))

    if os.path.isdir(data_source_dir):
        for root, _, files in os.walk(data_source_dir):
            for name in files:
                src_path = os.path.join(root, name)
                dst_path = os.path.join(data_dir, os.path.relpath(src_path, data_source_dir))
                shutil.copy(src_path, dst_path)

def after_upload(source, target, env, base="."):
    data_dir_path = os.path.join(base, "data")
    hasher = hashlib.sha1()

    if os.path.isdir(data_dir_path):
        for root, _, files in os.walk(data_dir_path):
            for name in files:
                with open(os.path.join(root, name), "rb") as f:
                    for chunk in iter(lambda: f.read(32768), b""):
                        hasher.update(chunk)

    current_sha1 = hasher.hexdigest()
    state_path = os.path.join(env.get("PROJECT_DIR"), ".uploadfs_sha1")
    if os.path.exists(state_path):
        with open(state_path, "r") as f:
            if f.read() == current_sha1:
                print("SPIFFS data are the same.")
                return

    print("SPIFFS data changed, running uploadfs target!")
    env.Execute("pio run -t uploadfs")

    with open(state_path, "w") as f:
        f.write(current_sha1)

if "Import" in locals():
    Import("env")
    base = os.path.abspath(".")
    env.AddPreAction("$BUILD_DIR/spiffs.bin", functools.partial(prepare_data_files, base=base))
    env.AddPostAction("upload", functools.partial(after_upload, base=base))

elif __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser()
    subparsers = parser.add_subparsers(dest='cmd')

    sub = subparsers.add_parser("prepare", help="Prepare files from data/ for SPIFFS")

    args = parser.parse_args()

    env = {
        "PROJECTDATA_DIR": "data",
    }

    if args.cmd == "prepare":
        prepare_data_files(env=env)
    else:
        parser.print_help()
        sys.exit(1)
