import subprocess
import sys

def run_atm_session(inputs):
    input_str = "\n".join(inputs) + "\n"
    res = subprocess.run(
        ["./atm_system"],
        input=input_str,
        text=True,
        capture_output=True
    )
    return res.stdout, res.stderr, res.returncode

def main():
    print("Running ATM Management System Test Suite...\n")
    tests_passed = 0
    total_tests = 10

    # Test Case 1: Correct PIN -> Login successful.
    stdout, _, _ = run_atm_session(["1234", "5"])
    if "Login successful" in stdout:
        print("[PASS] Test Case 1: Correct PIN -> Login successful.")
        tests_passed += 1
    else:
        print("[FAIL] Test Case 1: Correct PIN failed.")

    # Test Case 2: Wrong PIN -> Incorrect PIN.
    stdout, _, _ = run_atm_session(["9999"])
    if "Incorrect PIN" in stdout:
        print("[PASS] Test Case 2: Wrong PIN -> Access denied / Incorrect PIN.")
        tests_passed += 1
    else:
        print("[FAIL] Test Case 2: Wrong PIN failed.")

    # Test Case 3: Check balance -> Shows Rs. 10,000.00 initially.
    stdout, _, _ = run_atm_session(["1234", "1", "5"])
    if "Current Balance = Rs. 10000.00" in stdout:
        print("[PASS] Test Case 3: Check balance shows Rs. 10000.00 initially.")
        tests_passed += 1
    else:
        print("[FAIL] Test Case 3: Check balance failed.")

    # Test Case 4: Deposit Rs. 2,000 -> Balance becomes Rs. 12,000.00.
    stdout, _, _ = run_atm_session(["1234", "2", "2000", "1", "5"])
    if "Updated Balance = Rs. 12000.00" in stdout and "Current Balance = Rs. 12000.00" in stdout:
        print("[PASS] Test Case 4: Deposit Rs. 2,000 -> Balance becomes Rs. 12,000.00.")
        tests_passed += 1
    else:
        print("[FAIL] Test Case 4: Deposit Rs. 2,000 failed.")

    # Test Case 5: Withdraw Rs. 3,000 -> Balance becomes Rs. 7,000.00 (from 10,000 initial balance).
    stdout, _, _ = run_atm_session(["1234", "3", "3000", "1", "5"])
    if "Please collect your cash." in stdout and "Remaining Balance = Rs. 7000.00" in stdout:
        print("[PASS] Test Case 5: Withdraw Rs. 3,000 -> Balance becomes Rs. 7,000.00.")
        tests_passed += 1
    else:
        print("[FAIL] Test Case 5: Withdraw Rs. 3,000 failed.")

    # Test Case 6: Withdraw more than available balance -> Show insufficient balance.
    stdout, _, _ = run_atm_session(["1234", "3", "15000", "5"])
    if "Insufficient balance!" in stdout:
        print("[PASS] Test Case 6: Withdraw more than available balance -> Insufficient balance.")
        tests_passed += 1
    else:
        print("[FAIL] Test Case 6: Insufficient balance check failed.")

    # Test Case 7: Deposit zero or negative amount -> Show invalid amount.
    stdout, _, _ = run_atm_session(["1234", "2", "0", "2", "-500", "5"])
    if stdout.count("Invalid deposit amount!") >= 2:
        print("[PASS] Test Case 7: Deposit zero or negative amount -> Show invalid amount.")
        tests_passed += 1
    else:
        print("[FAIL] Test Case 7: Invalid deposit check failed.")

    # Test Case 8: Change PIN -> New PIN changed successfully.
    stdout, _, _ = run_atm_session(["1234", "4", "4321", "5"])
    if "PIN changed successfully!" in stdout:
        print("[PASS] Test Case 8: Change PIN successfully.")
        tests_passed += 1
    else:
        print("[FAIL] Test Case 8: Change PIN failed.")

    # Test Case 9: Invalid menu choice -> Show error message.
    stdout, _, _ = run_atm_session(["1234", "99", "5"])
    if "Invalid choice!" in stdout:
        print("[PASS] Test Case 9: Invalid menu choice -> Show error message.")
        tests_passed += 1
    else:
        print("[FAIL] Test Case 9: Invalid menu choice test failed.")

    # Test Case 10: Exit -> Display thank-you message.
    stdout, _, _ = run_atm_session(["1234", "5"])
    if "Thank you for using the ATM!" in stdout:
        print("[PASS] Test Case 10: Exit -> Display thank-you message.")
        tests_passed += 1
    else:
        print("[FAIL] Test Case 10: Exit message test failed.")

    print(f"\nResult: {tests_passed}/{total_tests} test cases passed.")

    if tests_passed == total_tests:
        sys.exit(0)
    else:
        sys.exit(1)

if __name__ == "__main__":
    main()
