{
  description = "animedoro's development shell.";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {nixpkgs, flake-utils, ...}:
    flake-utils.lib.eachDefaultSystem
      (system:
        let
          pkgs = import nixpkgs {
            inherit system;
          };
        in
        with pkgs; {
          devShells.default = mkShell {
            packages = [ fish ];
            buildInputs = [ clang-tools libGL raylib xorg.libX11 xorg.libXcursor xorg.libXrandr xorg.libXinerama xorg.libXi zig ];
          };

          shellHook = ''
            exec fish
          '';
        }
      );
}
