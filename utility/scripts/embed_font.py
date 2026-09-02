import pathlib
import argparse

def embed_font(srcDirPath: str, dstDirPath: str):
    srcDir = pathlib.Path(srcDirPath)
    dstDir = pathlib.Path(dstDirPath)

    srcFiles: list[pathlib.Path] = []
    srcFilesContent = []

    # Font files
    for shaderFile in srcDir.glob("*.ttf"):
        if shaderFile.is_file():
            srcFiles.append(shaderFile.absolute())

    for input_file in srcFiles:
        data = pathlib.Path(input_file).read_bytes()
        output_file = dstDir.joinpath(pathlib.Path(input_file.name + ".h"))
        
        with open(output_file, "w") as f:
            font_name = input_file.name.split('.')[0].replace('-', '_')
            
            f.write("#pragma once\n\n")
            f.write(f"static const unsigned char {font_name}_font_data[] = {{\n")

            for i in range(0, len(data), 16):
                chunk = data[i:i + 16]
                f.write("    ")
                f.write(", ".join(f"0x{b:02X}" for b in chunk))
                f.write(",\n" if i + 16 < len(data) else "\n")

            f.write("};\n")
            f.write(f"static const unsigned int font_data_size = {len(data)};\n")

        print(f"Generated {output_file}: {len(data)} bytes")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
                    prog='Embed Font Script',
                    description='Embed Font Script into project')

    parser.add_argument("--srcDir", type=str, help="Source Dir Path")
    parser.add_argument("--dstDir", type=str, help="Destination Dir Path")

    args = parser.parse_args()

    embed_font(args.srcDir, args.dstDir)
