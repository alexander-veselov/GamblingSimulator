import os
import sys

def getConfiguration(platform, type):
	OUT_FOLDER = 'out/build/'
	return os.path.join(OUT_FOLDER, f'{platform}-{type}')

def parseArgs(args):
	if len(args) == 1:
		return 'emscripten', 'debug'
	arg = args[1]
	platform = arg[:3]
	type = arg[3] if len(arg) == 4 else 'd'
	if platform != 'win' and platform != 'ems':
		print("Unexpected platform type. Use 'win' or 'ems'")
		exit(-1)
	if type != 'd' and type != 'r':
		print("Unexpected built type. Use 'd' or 'r'")
		exit(-2)
	return platform.replace('ems', 'emscripten').replace('win', 'x64'), \
		   type.replace('d', 'debug').replace('r', 'release')

def main(args):
	# TODO: add full rebuild option
	# TODO: add build add option
	platform, type = parseArgs(args)
	configuration = getConfiguration(platform, type)
	print(f'Building {configuration}.')
	return os.system(f'cmake --build {configuration}')

if __name__ == '__main__':
	sys.exit(main(sys.argv))