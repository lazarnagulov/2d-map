#pragma once

class Layer {
public:
    virtual ~Layer() = default;

    virtual void OnAttach() {}      
    virtual void OnDetach() {}     

    virtual void OnUpdate(float deltaTime) {} 
    virtual void OnRender() {}       

    virtual void OnKey(int key, int action) {}
    virtual void OnMouseButton(int button, int action, double x, double y) {}
    virtual void OnMouseMove(double x, double y) {}
};