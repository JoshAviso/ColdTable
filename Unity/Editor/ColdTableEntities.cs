using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class ColdTableScene
{
    public string SceneName;
    public List<ColdTableObject> Objects;
}

[System.Serializable]
public class ColdTableObject
{
    public string Name;
    public bool Enabled;
    public ColdTableTransform Transform;
    public List<ColdTableComponentWrapper> Components;
}

[System.Serializable]
public class ColdTableTransform
{
    public Vector3 Position;
    public Quaternion Rotation;
    public Vector3 Scale;
}

[System.Serializable]
public class ColdTableComponentWrapper
{
    public int ComponentType;
    public bool Enabled;
    public string componentJson;
    public int BodyType;
    public float Mass;
    public string MeshID;
    public string MaterialID;
}

[System.Serializable]
public enum ColdTableComponentType
{
    None = 0,
    Rigidbody = 3,
    Material = 4,
    Mesh = 5,
}

[System.Serializable]
public enum ColdTableRigidbodyType
{
    None = -1,
    Static = 0,
    Kinematic = 1,
    Dynamic = 2,
}