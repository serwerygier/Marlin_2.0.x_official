#
# download_mks_assets.py
#
Import("env")
import os,requests,zipfile,tempfile,shutil

url = "https://github.com/makerbase-mks/Mks-Robin-Nano-Marlin2.0-Firmware/archive/master.zip"
zip_path = os.path.join(env.Dictionary("PROJECT_LIBDEPS_DIR"), "mks-assets.zip")
assets_path = os.path.join(env.Dictionary("PROJECT_BUILD_DIR"), env.Dictionary("PIOENV"), "assets")

def download_mks_assets():
	print("Downloading MKS Assets")
	r = requests.get(url, stream=True)
	# the user may have a very clean workspace,
	# so create the PROJECT_LIBDEPS_DIR directory if not exits
	if os.path.exists(env.Dictionary("PROJECT_LIBDEPS_DIR")) == False:
		os.mkdir(env.Dictionary("PROJECT_LIBDEPS_DIR"))
	with open(zip_path, 'wb') as fd:
		for chunk in r.iter_content(chunk_size=128):
			fd.write(chunk)

def copy_mks_assets():
	print("Copying MKS Assets")
	output_path = tempfile.mkdtemp()
	zip_obj = zipfile.ZipFile(zip_path, 'r')
	zip_obj.extractall(output_path)
	zip_obj.close()
	if os.path.exists(assets_path) == True and os.path.isdir(assets_path) == False:
		os.unlink(assets_path)
	if os.path.exists(assets_path) == False:
		os.mkdir(assets_path)
	base_path = ''
	for filename in os.listdir(output_path):
		base_path = filename
	for filename in os.listdir(os.path.join(output_path, base_path, 'Firmware', 'mks_font')):
		shutil.copy(os.path.join(output_path, base_path, 'Firmware', 'mks_font', filename), assets_path)
	for filename in os.listdir(os.path.join(output_path, base_path, 'Firmware', 'mks_pic')):
		shutil.copy(os.path.join(output_path, base_path, 'Firmware', 'mks_pic', filename), assets_path)
	shutil.rmtree(output_path, ignore_errors=True)


#Malderin
#Секция загрузки моего лого к прошивке

url1 = "https://github.com/Malderin/Marlin_2.0.x_official/raw/Marlin-2.0_bugfix_new/Download/master1.zip"
zip_path1 = os.path.join(env.Dictionary("PROJECT_LIBDEPS_DIR"), "mks-assets1.zip")
assets_path1 = os.path.join(env.Dictionary("PROJECT_BUILD_DIR"), env.Dictionary("PIOENV"), "assets")

def download_mks_assets1():
	print("Downloading Logo KingRoonKP3")
	r = requests.get(url1, stream=True)
	# the user may have a very clean workspace,
	# so create the PROJECT_LIBDEPS_DIR directory if not exits
	if os.path.exists(env.Dictionary("PROJECT_LIBDEPS_DIR")) == False:
		os.mkdir(env.Dictionary("PROJECT_LIBDEPS_DIR"))
	with open(zip_path1, 'wb') as fd:
		for chunk in r.iter_content(chunk_size=128):
			fd.write(chunk)

def copy_mks_assets1():
	print("Copying Logo KingRoonKP3")
	output_path = tempfile.mkdtemp()
	zip_obj = zipfile.ZipFile(zip_path1, 'r')
	zip_obj.extractall(output_path)
	zip_obj.close()
	if os.path.exists(assets_path1) == True and os.path.isdir(assets_path1) == False:
		os.unlink(assets_path1)
	if os.path.exists(assets_path1) == False:
		os.mkdir(assets_path1)
	base_path = ''
	for filename in os.listdir(output_path):
		base_path = filename
	for filename in os.listdir(os.path.join(output_path, base_path, 'Firmware', 'mks_font')):
		shutil.copy(os.path.join(output_path, base_path, 'Firmware', 'mks_font', filename), assets_path1)
	for filename in os.listdir(os.path.join(output_path, base_path, 'Firmware', 'mks_pic')):
		shutil.copy(os.path.join(output_path, base_path, 'Firmware', 'mks_pic', filename), assets_path1)
	shutil.rmtree(output_path, ignore_errors=True)

if os.path.exists(zip_path1) == False:
	download_mks_assets()
	download_mks_assets1()

if os.path.exists(assets_path1) == False:
	copy_mks_assets()
	copy_mks_assets1()
