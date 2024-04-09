{pkgs ? import <nixpkgs> {}}:

pkgs.mkShell {
  packages = with pkgs; [ zig zls ];
  buildInputs = with pkgs; [ libGL xorg.libX11 xorg.libXcursor xorg.libXrandr xorg.libXinerama xorg.libXi ];
}