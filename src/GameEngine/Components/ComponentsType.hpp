#include <string>
#include <unordered_map>

namespace GameEngine {
    class ComponentsType {
    public:
        ComponentsType();
        ~ComponentsType();

        static size_t getNewComponentType();
        static size_t getNewComponentType(const std::string& componentName);
        static size_t getComponentType(const std::string& componentName);

    private:
        static size_t& getComponentTypeCounter();
        static std::unordered_map<std::string, size_t>& getComponentTypeMap();
        static size_t componentTypeCounter;
    };
} // namespace GameEngine
