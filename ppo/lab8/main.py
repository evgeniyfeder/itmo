from profiler.profiler import Profiler

import argparse

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-m", "--module", help="Module to profile")
    parser.add_argument("-f", "--function")
    parser.add_argument("--function-module")

    args = parser.parse_args()

    profiler = Profiler(args.module)
    profiler.profile(args.function_module, args.function)


if __name__ == '__main__':
    main()
