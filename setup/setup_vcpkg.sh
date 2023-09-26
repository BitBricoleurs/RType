LIBRARIES=(
  "vcpkg-tool-ninja"
  "raylib"
)

for LIB in "${LIBRARIES[@]}"; do
  ./vcpkg/vcpkg install $LIB
done

echo "Installation terminée !"
