import os
import sys
import json
import subprocess

def run(configuration):
	print(f'Runnning {configuration}')
	platform, buildType = configuration.split(' ')
	if platform != 'Emscripten':
		print('Supports only Emscripten platform')
		return -2
	buildFolder = f'out/build/emscripten-{buildType}'
	#executableFile = os.path.join(buildFolder, 'RoflCasino.html')
	proc = subprocess.run(['emrun', buildFolder], shell=True)
	return proc.returncode

def main(args):
	try:
		with open('.vs/ProjectSettings.json') as f:
			data = json.load(f)
			return run(data['CurrentProjectSetting'])
	except Exception as e:
		print(e)
		return -1

if __name__ == '__main__':
	sys.exit(main(sys.argv))