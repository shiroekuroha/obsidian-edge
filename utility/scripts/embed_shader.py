import pathlib
import argparse


def embed_shader(srcDirPath: str, dstDirPath: str):
    srcDir = pathlib.Path(srcDirPath)
    dstDir = pathlib.Path(dstDirPath)

    srcFiles: list[pathlib.Path] = []
    srcFilesContent = []

    # Shader files
    for shaderFile in srcDir.glob("*.glsl"):
        if shaderFile.is_file():
            srcFiles.append(shaderFile.absolute())

    # Header file string
    for file in srcFiles:
        varPrefix = "static const char* const s_default_{}_shader = ".format(str(file.name).split('.')[0])
        text = pathlib.Path(file).read_text(encoding="utf-8")
        lines = text.split('\n')

        finalStr = varPrefix
        for line in lines:
            finalStr += "\"" + line + "\\n" + "\""  + "\n"
        finalStr += ";"
            
        srcFilesContent.append(finalStr)

    for index in range(len(srcFiles)):
        output = dstDir.joinpath(str(srcFiles[index].name) + ".h")
        output.write_text(srcFilesContent[index], encoding="utf-8")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
                    prog='Embed Shader Script',
                    description='Embed Shader Script into project')

    parser.add_argument("--srcDir", type=str, help="Source Dir Path")
    parser.add_argument("--dstDir", type=str, help="Destination Dir Path")

    args = parser.parse_args()

    embed_shader(args.srcDir, args.dstDir)
