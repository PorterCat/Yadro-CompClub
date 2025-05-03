import subprocess
import sys
from pathlib import Path

def main():
    exe = sys.argv[1]
    tests = Path("tests").glob("test*.txt")
    passed, failed = 0, 0

    for test in tests:
        result_file = Path("tests/pending/result" + test.stem[4:] + ".txt")
        if not result_file.exists(): continue

        output = subprocess.run([exe, str(test)], capture_output=True, text=True).stdout
        expected = result_file.read_text()
        
        if output.strip() == expected.strip():
            print(f"{test} is passed")
            passed += 1
        else:
            print(f"{test} is failed")
            failed += 1

    print(f"Passed: {passed}, Failed: {failed}")

if __name__ == "__main__":
    main()