import os
import subprocess as sp
import sys
import shutil
import threading
import time
from pathlib import *

def ShowError(msg: str):
    print(("[ Error ]: " if sys.platform == 'win32' else "\033[1;31m[ Error ]:\033[91m ") + str(msg))
    print("\033[0m")
    exit()

###################### CONST ########################
true = True
false = False
NAME = "JUAMP"
args = sys.argv


##################### EXIT CODES #####################
ErrorExit = 1
PermisionErrorExit = 2
FileNotFoundExit = 3
ProbablyWindowsIssueExit = 4                                  # lmao

####################### PATHs ########################
root = Path(__file__).parent
src = root/'src'
_bin = root/'bin'
tmp = root/'tmp'

###################### FLAGS #########################
clean = '--clean' in args or '-c' in args
useSysTmp = '--notmp' in args
CC = ["g++" if not '--useClang++' in args else 'clang++']
if '--static' in args or '-s' in args:
    print("\033[38;5;208m\033[1m[ WARNING ]\033[0m Static linking may not work if you do not have specific libraries installed, it is recommended to use dynamic linking (remove --static/-s flag)")
    CC.append('-static')
if '--debug' in args or '-d' in args:
    CC.append('-g')
    CC.append('-Wall')
    CC.append('-Wextra')
for arg in args:
    if arg.startswith('-o=') or arg.startswith('--opt='):
        target = arg.removeprefix('-o=' if arg.startswith('-o=') else '--opt=')
        try:
            target = int(target)
        except Exception:
            ShowError('not a valid option for --opt, allowed values: 0, 1, 2, 3')
            exit()
        pass
        if target < 4 or target > 0:
            CC.append(f'-O{str(target) if target != 1 else "0"}')
        else:
            ShowError('not a valid option for --opt, allowed values: 0, 1, 2, 3')
        pass
    pass
pass

# print(CC)

######################################################

try:
    def build():
        objFiles = []

        print("\033[1mCompiling...\033[0m")
        for srcfile in src.glob('**/*.cpp'):
            if useSysTmp:
                temp = Path('/tmp') if sys.platform != 'win32' else Path('C:/temp')
            else:
                temp = tmp
            pass

            temp.mkdir(parents=true, exist_ok=true)
            object_file = temp / (srcfile.stem + '.o')
            objFiles.append(object_file)

            ############################# ALIGMENT #############################
            print("\r" + " " * shutil.get_terminal_size().columns, end='', flush=True)
            print(f"\r{srcfile.name} -> {object_file.name}".ljust(shutil.get_terminal_size().columns - 10), end='', flush=true)
            sp.run([*CC, '-c', str(srcfile), '-o', str(object_file)], check=true)
            print("...  Done" if sys.platform == 'win32' else "\033[32;1m... Done\033[0m", end='', flush=true)
            time.sleep(0.3)
            #####################################################################
        pass
        print("\r" + " " * shutil.get_terminal_size().columns, end='', flush=True)
        print('\033[A'+('\r... Done' if sys.platform == 'win32' else '\033[32;1m... Done\033[0m'))

        print()
        return objFiles

    def link(objFiles: list[Path]):
        out = _bin/(f'{NAME}.elf' if sys.platform != 'win32' else f'{NAME}.exe')
        _bin.mkdir(parents=True, exist_ok=True)

        print('\033[1mlinking and interlinking...\033[0m\n')

        maxlen = max(len(obj.name) for obj in objFiles)

        def compilationEffects(objs: list[Path], stop: threading.Event, completed: list[Path]):
            for i, obj in enumerate(objs):
                if stop.is_set():
                    completed.extend(objs[i:])
                    break

                file = obj.name

                padding: int = (maxlen - len(file)) + 3
                arrow: str = "\033[1m║\033[0m" if i < len(objs) - 1 else "🮦"
                print(f'{file}{" " * padding} {arrow}' if not i == len(objs) - 1 else f'{file} {'═' * (padding - 1)} ╗')
                time.sleep(0.1)

        completed = []
        stopSignal = threading.Event()

        thread = threading.Thread(target=compilationEffects, args=(objFiles, stopSignal, completed))
        thread.start()

        try:
            sp.run([*CC, '-o', str(out), *map(str, objFiles)], check=True)
        finally:
            stopSignal.set()
            thread.join()
        pass

        for obj in completed:
            filename = obj.name
            padding = " " * ((maxlen - len(filename)) + 3)
            arrow = "║" if obj != objFiles[-1] else "🮦"
            print(f'{filename}{padding} {arrow}')
        print(f'\n             {out.name}')

        print('... Done' if sys.platform == 'win32' else '\033[32;1m... Done\033[0m')

    def Sep():
        w = shutil.get_terminal_size().columns
        sep = ("====----" * (w // len("====----") + 1))[:w]

        print(f'\n{sep}\n')

    def DownloadTomlPP():
        print("\033[1mDownloading toml++\033[0m" if sys.platform != 'win32' else "Downloading toml++")
        try:
            sp.run(['curl', '-s', 'https://raw.githubusercontent.com/marzer/tomlplusplus/master/toml.hpp', '-o', 'src/toml.hpp'])
        except (sp.CalledProcessError, FileExistsError, FileNotFoundError):
            if sys.platform == 'win32':
                ShowError(f"InstallNormalOperatingSystemError: It looks like you are using windows and don't have curl installed, download it manually from www.xyz.pl or install a normal operating system")
                exit(ProbablyWindowsIssueExit)
            else:
                ShowError(f"There was an error while downloading toml++, try to download it manually from https://github.com/marzer/tomlplusplus/blob/master/toml.hpp")
                exit(FileNotFoundExit)
        except (PermissionError, OSError):
            ShowError("There was an error while downloading toml++, check if the script is run with the right permissions")
            exit(PermisionErrorExit)
        except Exception as err:
            ShowError(f"There was an error while downloading toml++, try again: {err}")
            exit(ErrorExit)
        print("... Done" if sys.platform == 'win32' else "\033[32;1m... Done\033[0m")
        print()

    if __name__ == '__main__':
        if '--help' in args or '-h' in args:
            def f(clr, text):
                if sys.platform == 'win32':
                    return text
                return f'\033[{clr}m{text}\033[0m'


            print(f('35;1', '--help/-h:') + ' displays help')
            print(f('94;1', '--clean/-c:') + ' Cleans tmp/ and removes compiled parts')
            print(f('34;1', '--notmp:') + ' Uses system tmp directory instead of tmp/')
            print(f('36;1', '--useClang++:') + ' Uses clang++ instead of g++')
            print(f('32;1', '--run/-r:') + ' Runs the program after compilation')
            print(f('33;1', "--static/-s:" + '\033[0m compiles with static linking'))
            print(f('31;1', "--debug/-d:" + '\033[0m compiles with debug flags'))
            print(f('38;5;10;1', '-o={value}/--opt={value}:'), "\033[0mSets the indicated compiler optimization level, available options: 0, 1, 2, 3")
            exit()
        if clean:
            if not _bin.exists() and not tmp.exists():
                print("Already cleaned!" if sys.platform == 'win32' else "\033[32;1mAlready cleaned!\033[0m")
                exit()
            print("Cleaning...")
            try:
                if _bin.exists():
                    print(f'deletion of {tmp.name}' if sys.platform == 'win32' else f'\033[91[deletion of {_bin.name}')
                    shutil.rmtree(_bin)
                time.sleep(0.5)
                if tmp.exists():
                    print(f'deletion of {tmp.name}' if sys.platform == 'win32' else f'\033[91[deletion of {tmp.name}')
                    shutil.rmtree(tmp)
                time.sleep(0.5)
                print('\033[0m' + '... Done' if sys.platform == 'win32' else '\033[32;1m... Done\033[0m')
            except (KeyboardInterrupt, SystemExit):
                exit()
            except (PermissionError, OSError):
                ShowError("There was an error while cleaning, check if the script is run with the right permissions")
                exit(PermisionErrorExit)
            except:
                ShowError("There was an error while cleaning, try again")
            finally:
                exit()
            pass
        pass

        print(f"{f'Building {NAME}':^{shutil.get_terminal_size().columns - len(f'Building {NAME}')}}")
        DownloadTomlPP()
        objFiles = build()
        Sep()
        link(objFiles)
        Sep()

        if useSysTmp:
            for obj in objFiles:
                os.remove(obj)
            pass
        pass

        if '--run' in args or '-r' in args:
            print(f"Running {NAME}...")
            time.sleep(1)
            try:
                sp.run(_bin/f'{NAME}.elf' if sys.platform != 'win32' else _bin/f'{NAME}.exe')
            except (KeyboardInterrupt, SystemExit):
                exit()
            except:
                ShowError(f"There was an error while running the program, try to run it yourself - ready binaries are in bin/{NAME}.{'elf' if sys.platform != 'win32' else 'exe'}")
            pass
        pass
    pass
except (KeyboardInterrupt, SystemExit):
    exit()
except sp.CalledProcessError as e:
    ShowError(f"""It appears that {CC[0]} returned an exit code different from 0
this means that the compilation failed, try removing unnecessary flags and try again""")
except (FileNotFoundError, FileExistsError):
    ShowError(f"""It looks like {CC[0]} is not installed on your system or is not in $PATH
install it and try again""")
    exit(FileNotFoundExit)
except (PermissionError, OSError):
    ShowError(f"""Unable to compile, by permissions problem
check if you are running this script with the right permissions""")
    exit(PermisionErrorExit)
except Exception as e:
    ShowError(f"There was an error while building, try again: {e}")
    exit(ErrorExit)