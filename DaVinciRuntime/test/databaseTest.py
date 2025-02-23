import sqlite3
import threading
import time
import sys

def main():
    global testPassed
    testPassed = False

    # Database connection details
    db_file = "../davinci.db"  # Update with the actual path to the running database

    # Set max test wait time (seconds)
    duration = 10

    # Event to signal that the table has been created
    table_created_event = threading.Event()

    # Function to simulate data insertion
    def simulate_data_insertion():
        global testPassed
        try:
            conn = sqlite3.connect(db_file)
            cursor = conn.cursor()
            cursor.execute("CREATE TABLE IF NOT EXISTS test_table (id INTEGER PRIMARY KEY AUTOINCREMENT, data TEXT)")
            table_created_event.set()  # Signal that the table has been created
            while not testPassed:
                cursor.execute("INSERT INTO test_table (data) VALUES (?)", (f"Data: {time.time()}",))
                conn.commit()
                time.sleep(5)  # Simulate data insertion every 5 seconds
            print("Thread Exiting")
            conn.close()
        except Exception as e:
            print(f"Data Insertion Error: {e}")
            testPassed = True

    # Function to verify data insertion
    def verify_data_insertion():
        global testPassed
        try:
            # Wait for the table to be created
            table_created_event.wait()
            conn = sqlite3.connect(db_file)
            cursor = conn.cursor()
            start_time = time.time()
            while not testPassed:
                cursor.execute("SELECT COUNT(*) FROM test_table")
                count = cursor.fetchone()[0]
                if count > 0:
                    print(f"Data found: {count} records")
                    print("Database Integration Test: PASSED!")
                    testPassed = True
                if time.time() - start_time >= duration:
                    break
            conn.close()
        except Exception as e:
            print(f"Data Verification Error: {e}")
            testPassed = True

    # Function to clean up the test environment
    def cleanup():
        try:
            conn = sqlite3.connect(db_file)
            cursor = conn.cursor()
            cursor.execute("DROP TABLE IF EXISTS test_table")
            conn.commit()
            conn.close()
            print("Cleanup completed: test_table deleted.")
        except Exception as e:
            print(f"Cleanup Error: {e}")

    # Start the data insertion simulation in a separate thread
    insertion_thread = threading.Thread(target=simulate_data_insertion).start()

    # Start the data verification
    verify_data_insertion()

    if not testPassed:
        print("Database Integration Test: FAILED!")

    # Perform cleanup
    cleanup()

    if testPassed:
        return_code = 1
    else:
        return_code = 0

    sys.exit(return_code)

if __name__ == "__main__":
    main()