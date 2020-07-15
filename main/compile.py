import sys
import os
import getopt
import time
startTime = time.time()
RED = "\033[1;31m"
BLUE = "\033[1;34m"
CYAN = "\033[1;36m"
GREEN = "\033[0;32m"
RESET = "\033[0;0m"
BOLD = "\033[;1m"
REVERSE = "\033[;7m"


def main(argv):
    cpp_file = ''
    exe_file = 'run'
    try:
        opts, args = getopt.getopt(argv, "hi:", ["help", 'ifile='])
    except getopt.GetoptError as err:
        print(err)
        usage()
        sys.exit(2)
    for o, a in opts:
        if o in ("-h", "--help"):
            usage()
            sys.exit()
        elif o in ("-i", "--ifile"):
            cpp_file = a + '.cpp'
            run(cpp_file, exe_file)


def usage():
    print('run_cpp.py -i <filename> (without extension)')


def getUptime():

    return time.time() - startTime


def run(cpp_file, exe_file):
    os.system("clear")
    print("-------------------")
    print("Starting Compilation...")
    sys.stdout.write(RED)
    print("  +Compiling " + cpp_file)
    sys.stdout.write(CYAN)

    if os.system('bazel build //main:main') == 0:
        print("")
        print("")
        print("Code Compiled Successfully")
        os.system('echo ./../bazel-bin/main/main > run')
        os.system('chmod +x run')
    else:
        print("")
        print("")
        print("Code Could Not Compile Successfully :(")
    sys.stdout.write(RESET)
    print("finished in:  '"+str(int(round(getUptime()))) + "' Second(s)")
    print("-------------------")


if __name__ == '__main__':
    main(sys.argv[1:])
