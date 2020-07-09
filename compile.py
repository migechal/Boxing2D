import sys
import os
import getopt


def main(argv):
    cpp_file = ''
    exe_file = 'run'
    try:
        opts, args = getopt.getopt(argv, "hi:", ["help", 'ifile='])
    except getopt.GetoptError as err:
        # print help information and exit
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


def run(cpp_file, exe_file):
    os.system("echo Starting Compilation...")
    os.system("echo Compiling " + cpp_file)
    if os.system('g++ ' + cpp_file + ' -g -o ' + exe_file + ' -lSDL2') == 0:
        os.system("echo Code Compiled Successfully")
    else:
        os.system("echo Code Could Not Compile Successfully :(")
    os.system("echo -------------------")


if __name__ == '__main__':
    main(sys.argv[1:])
