import os
import subprocess

def run_scripts_in_directory(directory):
    # List all files in the directory
    files = os.listdir(directory)
    
    # Filter out only Python scripts
    python_scripts = [f for f in files if f.endswith('.py')]
    
    # Dictionary to store the return codes
    return_codes = {}
    
    for script in python_scripts:
        script_path = os.path.join(directory, script)
        try:
            # Run the script and get the return code
            print("Running Test: " + script_path)
            process = subprocess.Popen(['python', script_path], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
            # Read and print the output in real-time
            while True:
                output = process.stdout.readline()
                if output == '' and process.poll() is not None:
                    break
                if output:
                    print(output.strip())

            return_codes[script] = process.poll()
        except Exception as e:
            return_codes[script] = f"Error: {e}"
    
    return return_codes

directory = '.'
return_codes = run_scripts_in_directory(directory)

for script, code in return_codes.items():
    print(f"Script: {script}, Return Code: {code}")
