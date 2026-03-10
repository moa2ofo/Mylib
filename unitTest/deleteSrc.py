import os
import shutil

def delete_files_in_src(root):
    for current_path, dirs, files in os.walk(root):
        # Se la cartella corrente si chiama "src"
        if os.path.basename(current_path) == "src":
            for f in files:
                file_path = os.path.join(current_path, f)
                try:
                    os.remove(file_path)
                    print(f"Eliminato file: {file_path}")
                except Exception as e:
                    print(f"Errore eliminando {file_path}: {e}")

if __name__ == "__main__":
    script_dir = os.path.dirname(os.path.abspath(__file__))
    delete_files_in_src(script_dir)
    print("Pulizia completata.")