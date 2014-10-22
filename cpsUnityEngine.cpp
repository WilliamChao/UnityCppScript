﻿#include "cpsInternal.h"
#include "cpsUtils.h"
#include "cpsUnityEngine.h"


#define cpsBindClass(...)\
    static cpsCachedClass s_class;\
    if (!s_class) { s_class = GetImage().findClass(__VA_ARGS__); }\
    return s_class;

#define cpsBindMethod(...)\
    static cpsCachedMethod s_method;\
    if (!s_method) { s_method = getClass().findMethod(__VA_ARGS__); }


namespace cpsUnityEngine
{

const Vector2 Vector2::zero = Vector2(0.0f, 0.0f);
const Vector2 Vector2::one = Vector2(1.0f, 1.0f);

const Vector3 Vector3::zero = Vector3(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::one = Vector3(1.0f, 1.0f, 1.0f);
const Vector3 Vector3::up = Vector3(0.0f, 1.0f, 0.0f);

const Vector4 Vector4::zero = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::one = Vector4(1.0f, 1.0f, 1.0f, 1.0f);



cpsImage& GetImage()
{
    static cpsCachedImage s_image;
    if (!s_image) { s_image = cpsImage::findImage("UnityEngine"); }
    return s_image;
}



/*static*/ cpsClass Application::getClass()
{
    cpsBindClass("UnityEngine", "Application");
}

/*static*/ const char* Application::get_dataPath()
{
    cpsBindMethod("get_dataPath");
    cpsObject ret = s_method.invoke(nullptr, nullptr);
    return cpsToUTF8(ret);
}

/*static*/ bool Application::get_isEditor()
{
    cpsBindMethod("get_isEditor");
    cpsObject ret = s_method.invoke(nullptr, nullptr);
    return *((gboolean*)ret.getDataPtr()) != 0;
}



/*static*/ cpsClass Debug::getClass()
{
    cpsBindClass("UnityEngine", "Debug");
}

/*static*/ void Debug::Log(const char *message)
{
    cpsBindMethod("Log", 1);

    MonoString *str = (MonoString*)cpsNewString(message);
    void *args[] = { str };
    s_method.invoke(nullptr, args);
}

/*static*/ void Debug::Log(const char *message, cpsObject obj)
{
    cpsBindMethod("Log", 2);

    MonoString *str = (MonoString*)cpsNewString(message);
    void *args[] = { str, obj };
    s_method.invoke(nullptr, args);
}

/*static*/ cpsClass Graphics::getClass()
{
    cpsBindClass("UnityEngine", "Graphics");
}


/*static*/ cpsClass Object::getClass() { cpsBindClass("UnityEngine", "Object"); }
Object::Object(cpsObject v) : super(v) {}

const char* Object::get_name() const
{
    cpsBindMethod("get_name");
    return cpsToUTF8(s_method.invoke(mobj));
}
void Object::set_name(const char *name)
{
    cpsBindMethod("set_name");
    void *args[] = { cpsNewString(name) };
    s_method.invoke(mobj, args);
}
HideFlags Object::get_hideFlags() const
{
    cpsBindMethod("get_hideFlags");
    return s_method.invoke(mobj).getData<HideFlags>();
}
void Object::set_hideFlags(HideFlags flags)
{
    cpsBindMethod("set_hideFlags");
    void *args[] = { &flags };
    s_method.invoke(mobj, args);
}
void* Object::obj_address() const
{
    cpsBindMethod("obj_address");
    return s_method.invoke(mobj).getData<void*>();
}

int Object::GetInstanceID() const
{
    cpsBindMethod("GetInstanceID");
    return s_method.invoke(mobj).getData<int>();
}
const char* Object::ToString() const
{
    cpsBindMethod("ToString");
    return cpsToUTF8(s_method.invoke(mobj));
}

/*static*/ Object Object::Instantiate(Object original, const Vector3 &position, const Quaternion &rotation)
{
    cpsBindMethod("Instantiate", 3);
    void *args[] = { original, (void*)&position, (void*)&rotation };
    return s_method.invoke(nullptr, args).getData<void*>();
}
/*static*/ Object Object::Instantiate(Object original)
{
    cpsBindMethod("Instantiate", 1);
    void *args[] = { original };
    return s_method.invoke(nullptr, args).getData<void*>();
}
/*static*/ void Object::Destroy(cpsObject obj, float delay)
{
    cpsBindMethod("Destroy", 2);
    void *args[] = { obj, &delay };
    s_method.invoke(nullptr, args);
}
/*static*/ void Object::DestroyImmediate(Object obj, bool allowDestroyingAssets)
{
    cpsBindMethod("DestroyImmediate", 2);
    gboolean b = allowDestroyingAssets;
    void *args[] = { obj, &b };
    s_method.invoke(nullptr, args);
}
/*static*/ void Object::DontDestroyOnLoad(Object obj)
{
    cpsBindMethod("DontDestroyOnLoad", 1);
    void *args[] = { obj };
    s_method.invoke(nullptr, args);
}
/*static*/ void Object::DestroyObject(Object obj, float delay)
{
    cpsBindMethod("DestroyObject", 2);
    void *args[] = { obj, &delay };
    s_method.invoke(nullptr, args);
}



/*static*/ cpsClass Texture::getClass() { cpsBindClass("UnityEngine", "Texture"); }
Texture::Texture(cpsObject v) : super(v) {}



/*static*/ cpsClass RenderTexture::getClass() { cpsBindClass("UnityEngine", "RenderTexture"); }
RenderTexture::RenderTexture(cpsObject v) : super(v) {}



/*static*/ cpsClass ComputeBuffer::getClass() { cpsBindClass("UnityEngine", "ComputeBuffer"); }
ComputeBuffer::ComputeBuffer(cpsObject v) : super(v) {}



/*static*/ cpsClass PhysicMaterial::getClass() { cpsBindClass("UnityEngine", "PhysicMaterial"); }
PhysicMaterial::PhysicMaterial(cpsObject v) : super(v) {}



/*static*/ cpsClass PhysicMaterial2D::getClass() { cpsBindClass("UnityEngine", "PhysicMaterial2D"); }
PhysicMaterial2D::PhysicMaterial2D(cpsObject v) : super(v) {}



/*static*/ cpsClass GameObject::getClass() { cpsBindClass("UnityEngine", "GameObject"); }
GameObject::GameObject(cpsObject v) : super(v) {}



/*static*/ cpsClass Behaviour::getClass() { cpsBindClass("UnityEngine", "Behaviour"); }
Behaviour::Behaviour(cpsObject obj) : super(obj) {}

bool Behaviour::get_enabled() const
{
    cpsBindMethod("get_enabled");
    return s_method.invoke(mobj).getData<gboolean>() != 0;
}
void Behaviour::set_enabled(bool v)
{
    cpsBindMethod("set_enabled");
    gboolean b = v;
    void *args[] = { &b };
    s_method.invoke(mobj, args);
}



/*static*/ cpsClass Component::getClass() { cpsBindClass("UnityEngine", "Component"); }
Component::Component(cpsObject obj) : super(obj) {}

GameObject Component::get_gameObject() const
{
    cpsBindMethod("get_gameObject");
    return s_method.invoke(mobj).getData<void*>();
}
bool Component::get_active() const
{
    cpsBindMethod("get_active");
    return s_method.invoke(mobj).getData<gboolean>()!=0;
}
void Component::set_active(bool v)
{
    cpsBindMethod("set_active");
    gboolean b = v;
    void *args[] = { &b };
    s_method.invoke(mobj, args);
}
const char* Component::get_tag() const
{
    cpsBindMethod("get_tag");
    return cpsToUTF8(s_method.invoke(mobj));
}
void Component::set_tag(const char *v)
{
    cpsBindMethod("set_tag");
    void *args[] = { cpsNewString(v) };
    s_method.invoke(mobj, args);
}

bool Component::CompareTag(const char *v)
{
    cpsBindMethod("CompareTag", 1);
    void *args[] = { cpsNewString(v) };
    return s_method.invoke(mobj, args).getData<gboolean>()!=0;
}

void Component::SendMessageUpwards(const char *method_name, cpsObject obj, SendMessageOptions opt)
{
    cpsBindMethod("SendMessageUpwards", 3);
    void *args[] = { cpsNewString(method_name), obj, &opt };
    s_method.invoke(mobj, args);
}

void Component::SendMessage(const char *method_name, cpsObject obj, SendMessageOptions opt)
{
    cpsBindMethod("SendMessage", 3);
    void *args[] = { cpsNewString(method_name), obj, &opt };
    s_method.invoke(mobj, args);
}

void Component::BroadcastMessage(const char *method_name, cpsObject obj, SendMessageOptions opt)
{
    cpsBindMethod("BroadcastMessage", 3);
    void *args[] = { cpsNewString(method_name), obj, &opt };
    s_method.invoke(mobj, args);
}





/*static*/ cpsClass Transform::getClass() { cpsBindClass("UnityEngine", "Transform"); }
Transform::Transform(cpsObject obj) : super(obj) {}

Vector3 Transform::get_position() const
{
    cpsBindMethod("get_position");
    return s_method.invoke(mobj).getData<Vector3>();
}
void Transform::set_position(const Vector3& v)
{
    cpsBindMethod("set_position");
    void *args[] = { (void*)&v };
    s_method.invoke(mobj, args);
}

Vector3 Transform::get_localPosition() const
{
    cpsBindMethod("get_localPosition");
    return s_method.invoke(mobj).getData<Vector3>();
}
void Transform::set_localPosition(const Vector3& v)
{
    cpsBindMethod("set_localPosition");
    void *args[] = { (void*)&v };
    s_method.invoke(mobj, args);
}

Vector3 Transform::get_eulerAngles() const
{
    cpsBindMethod("get_eulerAngles");
    return s_method.invoke(mobj).getData<Vector3>();
}
void Transform::set_eulerAngles(const Vector3& v)
{
    cpsBindMethod("set_eulerAngles");
    void *args[] = { (void*)&v };
    s_method.invoke(mobj, args);
}

Vector3 Transform::get_right() const
{
    cpsBindMethod("get_right");
    return s_method.invoke(mobj).getData<Vector3>();
}
void Transform::set_right(const Vector3& v)
{
    cpsBindMethod("set_right");
    void *args[] = { (void*)&v };
    s_method.invoke(mobj, args);
}

Vector3 Transform::get_up() const
{
    cpsBindMethod("get_up");
    return s_method.invoke(mobj).getData<Vector3>();
}
void Transform::set_up(const Vector3& v)
{
    cpsBindMethod("set_up");
    void *args[] = { (void*)&v };
    s_method.invoke(mobj, args);
}

Vector3 Transform::get_forward() const
{
    cpsBindMethod("get_forward");
    return s_method.invoke(mobj).getData<Vector3>();
}
void Transform::set_forward(const Vector3& v)
{
    cpsBindMethod("set_forward");
    void *args[] = { (void*)&v };
    s_method.invoke(mobj, args);
}

Quaternion Transform::get_rotation() const
{
    cpsBindMethod("get_rotation");
    return s_method.invoke(mobj).getData<Quaternion>();
}
void Transform::set_rotation(const Quaternion &v)
{
    cpsBindMethod("set_rotation");
    void *args[] = { (void*)&v };
    s_method.invoke(mobj, args);
}

Quaternion Transform::get_localRotation() const
{
    cpsBindMethod("get_localRotation");
    return s_method.invoke(mobj).getData<Quaternion>();
}
void Transform::set_localRotation(const Quaternion &v)
{
    cpsBindMethod("set_localRotation");
    void *args[] = { (void*)&v };
    s_method.invoke(mobj, args);
}

Vector3 Transform::get_localScale() const
{
    cpsBindMethod("get_localScale");
    return s_method.invoke(mobj).getData<Vector3>();
}
void Transform::set_localScale(const Vector3& v)
{
    cpsBindMethod("set_localScale");
    void *args[] = { (void*)&v };
    s_method.invoke(mobj, args);
}

Transform Transform::get_parent() const
{
    cpsBindMethod("get_parent");
    return s_method.invoke(mobj);
}
void Transform::set_parent(const Transform &v)
{
    cpsBindMethod("set_parent");
    void *args[] = { (void*)v };
    s_method.invoke(mobj, args);
}

Matrix4x4 Transform::get_worldToLocalMatrix() const
{
    cpsBindMethod("get_worldToLocalMatrix");
    return s_method.invoke(mobj).getData<Matrix4x4>();
}
Matrix4x4 Transform::get_localToWorldMatrix() const
{
    cpsBindMethod("get_localToWorldMatrix");
    return s_method.invoke(mobj).getData<Matrix4x4>();
}

Transform Transform::get_root()
{
    cpsBindMethod("get_root");
    return s_method.invoke(mobj);
}
int Transform::get_childCount()
{
    cpsBindMethod("get_childCount");
    return s_method.invoke(mobj).getData<int>();
}
Vector3 Transform::get_lossyScale()
{
    cpsBindMethod("get_lossyScale");
    return s_method.invoke(mobj).getData<Vector3>();
}

bool Transform::get_hasChanged()
{
    cpsBindMethod("get_hasChanged");
    return s_method.invoke(mobj).getData<gboolean>()!=0;
}
void Transform::set_hasChanged(bool v)
{
    cpsBindMethod("set_hasChanged");
    gboolean b = v;
    void *args[] = {&b};
    s_method.invoke(mobj, args);
}


void Transform::Translate(const Vector3& v, Space s)
{
    static const char *typenames[] = {"UnityEngine.Vector3", "UnityEngine.Space"};
    cpsBindMethod("Translate", 2, typenames);
    void *args[] = { (void*)&v, &s };
    s_method.invoke(mobj, args);
}
void Transform::Translate(const Vector3& v, Transform relative)
{
    static const char *typenames[] = { "UnityEngine.Vector3", "UnityEngine.Transform" };
    cpsBindMethod("Translate", 2, typenames);
    void *args[] = { (void*)&v, relative.mobj };
    s_method.invoke(mobj, args);
}

void Transform::Rotate(const Vector3& eulerAngles, Space s)
{
    static const char *typenames[] = { "UnityEngine.Vector3", "UnityEngine.Space" };
    cpsBindMethod("Rotate", 2, typenames);
    void *args[] = { (void*)&eulerAngles, &s };
    s_method.invoke(mobj, args);
}
void Transform::Rotate(const Vector3& axis, float angle, Space s)
{
    static const char *typenames[] = { "UnityEngine.Vector3", "System.Single", "UnityEngine.Space" };
    cpsBindMethod("Rotate", 3, typenames);
    void *args[] = { (void*)&axis, &angle, &s };
    s_method.invoke(mobj, args);
}
void Transform::RotateAround(const Vector3& point, const Vector3& axis, float angle)
{
    static const char *typenames[] = { "UnityEngine.Vector3", "UnityEngine.Vector3", "System.Single" };
    cpsBindMethod("RotateAround", 3, typenames);
    void *args[] = { (void*)&point, (void*)&axis, &angle };
    s_method.invoke(mobj, args);
}

void Transform::LookAt(Transform t, const Vector3& up)
{
    static const char *typenames[] = { "UnityEngine.Transform", "UnityEngine.Vector3" };
    cpsBindMethod("LookAt", 2, typenames);
    void *args[] = { t.mobj, (void*)&up };
    s_method.invoke(mobj, args);
}
void Transform::LookAt(const Vector3& worldPos, const Vector3&up)
{
    static const char *typenames[] = { "UnityEngine.Vector3", "UnityEngine.Vector3" };
    cpsBindMethod("LookAt", 2, typenames);
    void *args[] = { (void*)&worldPos, (void*)&up };
    s_method.invoke(mobj, args);
}

Vector3 Transform::TransformDirection(const Vector3& v)
{
    cpsBindMethod("TransformDirection", 1);
    void *args[] = { (void*)&v };
    return s_method.invoke(mobj, args).getData<Vector3>();
}

Vector3 Transform::InverseTransformDirection(const Vector3& v)
{
    cpsBindMethod("InverseTransformDirection", 1);
    void *args[] = { (void*)&v };
    return s_method.invoke(mobj, args).getData<Vector3>();
}

Vector3 Transform::TransformPoint(const Vector3& v)
{
    cpsBindMethod("TransformPoint", 1);
    void *args[] = { (void*)&v };
    return s_method.invoke(mobj, args).getData<Vector3>();
}

Vector3 Transform::InverseTransformPoint(const Vector3& v)
{
    cpsBindMethod("InverseTransformPoint", 1);
    void *args[] = { (void*)&v };
    return s_method.invoke(mobj, args).getData<Vector3>();
}

void Transform::DetachChildren()
{
    cpsBindMethod("DetachChildren", 0);
    s_method.invoke(mobj);
}

void Transform::SetAsFirstSibling()
{
    cpsBindMethod("SetAsFirstSibling", 0);
    s_method.invoke(mobj);
}

void Transform::SetAsLastSibling()
{
    cpsBindMethod("SetAsLastSibling", 0);
    s_method.invoke(mobj);
}

void Transform::SetSiblingIndex(int i)
{
    cpsBindMethod("SetAsLastSibling", 1);
    void *args[] = { (void*)&i };
    s_method.invoke(mobj, args);
}

int Transform::GetSiblingIndex()
{
    cpsBindMethod("GetSiblingIndex", 0);
    return s_method.invoke(mobj).getData<int>();;
}

Transform Transform::Find(const char *name)
{
    cpsBindMethod("Find", 1);
    void *args[] = { cpsNewString(name) };
    return s_method.invoke(mobj, args).getData<void*>();
}

void Transform::SendTransformChangedScale()
{
    cpsBindMethod("SendTransformChangedScale", 0);
    s_method.invoke(mobj);
}

bool Transform::IsChildOf(Transform t)
{
    cpsBindMethod("IsChildOf", 1);
    void *args[] = { t.mobj };
    return s_method.invoke(mobj, args).getData<gboolean>()!=0;
}

Transform Transform::FindChild(const char *name)
{
    cpsBindMethod("FindChild", 1);
    void *args[] = { cpsNewString(name) };
    return s_method.invoke(mobj, args).getData<void*>();
}

void Transform::RotateAround(const Vector3& axis, float a)
{
    cpsBindMethod("RotateAround", 2);
    void *args[] = { (void*)&axis, &a };
    s_method.invoke(mobj, args);
}

void Transform::RotateAroundLocal(const Vector3& axis, float a)
{
    cpsBindMethod("RotateAroundLocal", 2);
    void *args[] = { (void*)&axis, &a };
    s_method.invoke(mobj, args);
}

Transform Transform::GetChild(int i)
{
    cpsBindMethod("GetChild", 1);
    void *args[] = { &i };
    return s_method.invoke(mobj, args).getData<void*>();
}

int Transform::GetChildCount()
{
    cpsBindMethod("GetChildCount", 0);
    return s_method.invoke(mobj).getData<int>();
}

bool Transform::IsNonUniformScaleTransform()
{
    cpsBindMethod("IsNonUniformScaleTransform", 0);
    return s_method.invoke(mobj).getData<gboolean>()!=0;
}



/*static*/ cpsClass Rigidbody::getClass() { cpsBindClass("UnityEngine", "Rigidbody"); }
Rigidbody::Rigidbody(cpsObject obj) : super(obj) {}



/*static*/ cpsClass Rigidbody2D::getClass() { cpsBindClass("UnityEngine", "Rigidbody2D"); }
Rigidbody2D::Rigidbody2D(cpsObject obj) : super(obj) {}



/*static*/ cpsClass Collider::getClass() { cpsBindClass("UnityEngine", "Collider"); }
Collider::Collider(cpsObject obj) : super(obj) {}

bool Collider::get_enabled()
{
    cpsBindMethod("get_enabled");
    return s_method.invoke(mobj).getData<gboolean>() != 0;
}
void Collider::set_enabled(bool v)
{
    cpsBindMethod("set_enabled");
    gboolean b = v;
    void *args[] = {&b};
    s_method.invoke(mobj, args);
}

Rigidbody Collider::get_attachedRigidbody()
{
    cpsBindMethod("get_attachedRigidbody");
    return s_method.invoke(mobj).getData<void*>();
}
bool Collider::get_isTrigger()
{
    cpsBindMethod("get_isTrigger");
    return s_method.invoke(mobj).getData<gboolean>() != 0;
}
void Collider::set_isTrigger(bool v)
{
    cpsBindMethod("set_isTrigger");
    gboolean b = v;
    void *args[] = { &b };
    s_method.invoke(mobj, args);
}

PhysicMaterial Collider::get_material()
{
    cpsBindMethod("get_material");
    return s_method.invoke(mobj).getData<void*>();
}
void Collider::set_material(PhysicMaterial v)
{
    cpsBindMethod("set_material");
    void *args[] = { v.mobj };
    s_method.invoke(mobj, args);
}
PhysicMaterial Collider::get_sharedMaterial()
{
    cpsBindMethod("get_sharedMaterial");
    return s_method.invoke(mobj).getData<void*>();
}
void Collider::set_sharedMaterial(PhysicMaterial v)
{
    cpsBindMethod("set_sharedMaterial");
    void *args[] = { v.mobj };
    s_method.invoke(mobj, args);
}
Bounds Collider::get_bounds()
{
    cpsBindMethod("get_bounds");
    return s_method.invoke(mobj).getData<Bounds>();
}

Vector3 Collider::ClosestPointOnBounds(const Vector3 &v)
{
    cpsBindMethod("ClosestPointOnBounds");
    void *args[] = { (void*)&v };
    return s_method.invoke(mobj, args).getData<Vector3>();
}

bool Collider::Raycast(const Ray &ray, RaycastHit &hit, float dist)
{
    cpsBindMethod("Raycast");
    void *args[] = { (void*)&ray, (void*)&hit, &dist };
    return s_method.invoke(mobj, args).getData<gboolean>() != 0;
}



/*static*/ cpsClass Collider2D::getClass() { cpsBindClass("UnityEngine", "Collider2D"); }
Collider2D::Collider2D(cpsObject obj) : super(obj) {}



/*static*/ cpsClass Camera::getClass() { cpsBindClass("UnityEngine", "Camera"); }
Camera::Camera(cpsObject obj) : super(obj) {}



/*static*/ cpsClass Light::getClass() { cpsBindClass("UnityEngine", "Light"); }
Light::Light(cpsObject obj) : super(obj) {}





} // namespace cpsUnityEngine