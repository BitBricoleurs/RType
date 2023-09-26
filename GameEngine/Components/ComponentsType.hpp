#include <string>
#include <unordered_map>


namespace GameEngine {
    class ComponentsType {
    public:
        ComponentsType() = default;
        ~ComponentsType() = default;

        static size_t getNewComponentType() {
            return getComponentTypeCounter()++;
        }

        static size_t getNewComponentType(const std::string& componentName) {
            return getComponentTypeMap()[componentName] = getComponentTypeCounter()++;
        }

        static size_t getComponentType(const std::string& componentName) {
            return getComponentTypeMap()[componentName];
        }

    private:
        static size_t& getComponentTypeCounter() {
            static size_t componentTypeCounter = 0;
            return componentTypeCounter;
        }

        static std::unordered_map<std::string, size_t>& getComponentTypeMap() {
            static std::unordered_map<std::string, size_t> componentTypeMap;
            return componentTypeMap;
        }
    };
} // namespace GameEngine
