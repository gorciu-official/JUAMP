all:
	python3 build.py

download_toml:
	curl -s https://raw.githubusercontent.com/marzer/tomlplusplus/master/toml.hpp -o src/toml.hpp

gui:
	python3 build.py --gui