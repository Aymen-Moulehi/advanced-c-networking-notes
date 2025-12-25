import os
import subprocess
import sys

def find_c_files():
    """Finds all .c files in the current directory and subdirectories."""
    c_files = []
    for root, dirs, files in os.walk("."):
        # Ignore hidden folders like .git
        if ".git" in root or ".vscode" in root:
            continue
        for file in files:
            if file.endswith(".c"):
                c_files.append(os.path.join(root, file))
    return sorted(c_files)

def run_program():
    files = find_c_files()
    
    if not files:
        print("❌ No .c files found in the repository!")
        return

    print("\n--- Linux Network Dev Launcher ---")
    for i, file in enumerate(files):
        print(f"[{i}] {file}")

    try:
        choice = int(input("\nSelect the file number to run: "))
        selected_file = files[choice]
    except (ValueError, IndexError):
        print("❌ Invalid selection.")
        return

    # Prepare names
    executable = "temp_runner.out"
    
    # 1. Compile
    print(f"🔨 Compiling {selected_file}...")
    compile_cmd = ["gcc", selected_file, "-o", executable]
    
    # Note: If using threads later, we might need -pthread
    result = subprocess.run(compile_cmd)

    if result.returncode == 0:
        print(f"🚀 Running...\n" + "-"*30)
        try:
            # 2. Run
            subprocess.run(f"./{executable}", shell=True)
        except KeyboardInterrupt:
            print("\n🛑 Program stopped by user.")
        finally:
            # 3. Cleanup
            if os.path.exists(executable):
                os.remove(executable)
            print("-"*30 + "\n✨ Done.")
    else:
        print("❌ Compilation failed.")

if __name__ == "__main__":
    run_program()
