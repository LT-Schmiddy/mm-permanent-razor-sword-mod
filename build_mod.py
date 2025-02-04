import pathlib, subprocess, os, shutil, tomllib
import build_n64recomp_tools as bnt

project_root = pathlib.Path(__file__).parent

mod_data = tomllib.loads(project_root.joinpath("mod.toml").read_text())
mod_manifest_data = mod_data["manifest"]
# print(mod_data)
build_dir = project_root.joinpath(f"build")
build_nrm_file = build_dir.joinpath(f"{mod_data['inputs']['mod_filename']}.nrm")

runtime_mods_dir = project_root.joinpath("runtime/mods")
runtime_nrm_file = runtime_mods_dir.joinpath(f"{mod_data['inputs']['mod_filename']}.nrm")

def run_build():
    if not bnt.build_dir.exists():
        print("N64Recomp tools not built. Building now...")
        bnt.rebuild_tools();

    deps = bnt.deps

    make_run = subprocess.run(
        [
            deps["make"],
        ],
        cwd=pathlib.Path(__file__).parent
    )
    if make_run.returncode != 0:
        raise RuntimeError("Make failed to build mod binaries.")

    RecompModTool_run = subprocess.run(
        [
            bnt.get_RecompModTool_path(),
            "mod.toml",
            "build"
        ],
        cwd=pathlib.Path(__file__).parent
    )
    if RecompModTool_run.returncode != 0:
        raise RuntimeError("RecompModTool failed to build mod.")



    # Copying files for debugging:
    os.makedirs(runtime_mods_dir, exist_ok=True)
    shutil.copy(build_nrm_file, runtime_nrm_file)

if __name__ == '__main__':
    run_build()