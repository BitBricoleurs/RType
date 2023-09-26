LIBRARIES=(
  "vcpkg-tool-ninja"
  "glfw3"
)

for LIB in "${LIBRARIES[@]}"; do
  ./vcpkg/vcpkg install $LIB
done

echo "Installation terminée !"
