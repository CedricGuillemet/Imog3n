#pragma once

#include <vector>
#include <map>
#include <string>
#include <utility>
#include <functional>

namespace Imog3n
{
    class Node
    {
        
        
        public:
        Node() {}
        
        virtual ~Node() {}
        
        static Node* Create(const std::string& name)
        {
            auto iter = m_descriptions.find(name);
            if (iter != m_descriptions.end())
            {
                auto* node = iter->second->m_makeNew();
                node->m_description = iter->second;
                return node;
            }
            return nullptr;
        }
    
        class Description
        {
        public:
            Description() {}
            Description(const char* name, std::function<Node*()>&& makeNew)
                : m_makeNew{std::move(makeNew)}
            {
                
            }
            
            Description& Input(const char* name)
            {
                m_inputs.push_back(name);
                return *this;
            }
            
            Description& Output(const char* name)
            {
                m_outputs.push_back(name);
                return *this;
            }
            
            Description& Parameter(const char* name)
            {
                m_parameters.push_back(name);
                return *this;
            }

            std::vector<const char*> m_inputs{};
            std::vector<const char*> m_outputs{};
            std::vector<const char*> m_parameters{};
            std::function<Node*()> m_makeNew{};
        };
        
        Node(Description* description)
            : m_description(description)
        {
        }
        
        template<typename T> static Description& NewDescription(const char* name)
        {
            m_descriptions[name] = new Description(name, [](){ return new T; });
            return *m_descriptions[name];
        }
        
        Description* m_description;
        
        static std::map<std::string, Description*> m_descriptions;
        
    };

/*
class Circle : public Node
{
    public:
    Circle();
    
    float m_radius{0.3f};

    static inline Description _description{NewDescription<Circle>("Circle")
        .Input("myInput")
        .Output("myOutput")
        .Parameter("m_radius")
    };
};

Circle::Circle()
    : Node()
{
    
}
*/
}
