import subprocess
import sys
from pathlib import Path

def trim_empty(lines):
    start = 0
    while start < len(lines) and lines[start].strip() == '':
        start += 1
    end = len(lines) - 1
    while end >= 0 and lines[end].strip() == '':
        end -= 1
    return lines[start:end+1] if start <= end else []

def main():
    exe = sys.argv[1]
    tests = Path("tests").glob("test*.txt")
    passed, failed = 0, 0

    for test in tests:
        result_file = Path("tests/pending/result" + test.stem[4:] + ".txt")
        if not result_file.exists():
            continue

        process = subprocess.run([exe, str(test)], capture_output=True, text=True)
        output = process.stdout
        expected = result_file.read_text()

        output_lines = [line.rstrip() for line in output.splitlines()]
        expected_lines = [line.rstrip() for line in expected.splitlines()]

        output_trimmed = trim_empty(output_lines)
        expected_trimmed = trim_empty(expected_lines)

        if output_trimmed == expected_trimmed:
            print(f"{test} is passed")
            passed += 1
        else:
            print(f"{test} is failed")
            failed += 1

            max_lines = max(len(output_trimmed), len(expected_trimmed))
            for i in range(max_lines):
                line_out = output_trimmed[i] if i < len(output_trimmed) else None
                line_exp = expected_trimmed[i] if i < len(expected_trimmed) else None

                if line_out != line_exp:
                    print(f"Difference at line {i + 1}:")
                    print(f"Output:  {line_out}" if line_out is not None else "Output:  <missing>")
                    print(f"Expected: {line_exp}" if line_exp is not None else "Expected: <missing>")
                    break

    print(f"Passed: {passed}, Failed: {failed}")

if __name__ == "__main__":
    main()