using UnityEngine;
using UnityEditor;
using System.IO;
using System.Collections.Generic;
using UnityEngine.SceneManagement;
using UnityEditor.SceneManagement;

public class ColdTableScenePlugin : EditorWindow
{
    string jsonFilePath = "";
    public string sceneAssetPath = "";
    ColdTableScene data;
    private static Mesh cubeMesh = null;
    private static Mesh sphereMesh = null;
    private static Mesh capsuleMesh = null;
    private static Mesh cylinderMesh = null;
    private static Mesh planeMesh = null;
    private static Mesh quadMesh = null;

    // Call this once to cache Unity's built-in primitive meshes
    [InitializeOnLoadMethod]
    public static void CachePrimitiveMeshes()
    {
        cubeMesh = PrimitiveMesh(PrimitiveType.Cube);
        sphereMesh = PrimitiveMesh(PrimitiveType.Sphere);
        capsuleMesh = PrimitiveMesh(PrimitiveType.Capsule);
        cylinderMesh = PrimitiveMesh(PrimitiveType.Cylinder);
        planeMesh = PrimitiveMesh(PrimitiveType.Plane);
        quadMesh = PrimitiveMesh(PrimitiveType.Quad);
    }

    [MenuItem("Tools/Cold Table Scene Plugin")]
    public static void ShowWindow()
    {
        GetWindow<ColdTableScenePlugin>("Cold Table Scene Plugin");
    }

    void OnGUI()
    {
        GUILayout.Label("Cold Table Scene Plugin", EditorStyles.boldLabel);


        EditorGUI.BeginDisabledGroup(string.IsNullOrEmpty(sceneAssetPath));
        if (GUILayout.Button("Load Cold Table Scene"))
        {
            jsonFilePath = EditorUtility.OpenFilePanel("Select Salad file", "", "salad");
            if (!string.IsNullOrEmpty(jsonFilePath))
            {
                string json = File.ReadAllText(jsonFilePath);
                data = JsonUtility.FromJson<ColdTableScene>(json);
                WriteScene(data, true);
            }
        }
        EditorGUI.EndDisabledGroup();
        sceneAssetPath = EditorGUILayout.TextField("Load Scene Path", sceneAssetPath);

        if (GUILayout.Button("Save Current as Cold Table Scene"))
        {
            string savePath = EditorUtility.SaveFilePanel("Save Scene as Cold Table Scene", "", "DefaultScene.salad", "salad");
            if (!string.IsNullOrEmpty(savePath))
            {
                data = InterpretActiveScene();
                string json = JsonUtility.ToJson(data, true);
                File.WriteAllText(savePath, json);
                AssetDatabase.Refresh();
            }
        }

        /*
        if (data != null)
        {
            data.SceneName = EditorGUILayout.TextField("SceneName", data.SceneName);
            EditorGUI.indentLevel++;
            foreach (var obj in data.Objects)
            {
                obj.Name = EditorGUILayout.TextField("Name", obj.Name);
                obj.Enabled = EditorGUILayout.Toggle("Enabled", obj.Enabled);

                EditorGUI.indentLevel++;
                foreach (var component in obj.Components)
                {
                    if (component != null)
                    {
                        component.ComponentType = EditorGUILayout.IntField("ComponentType", component.ComponentType);
                        component.Enabled = EditorGUILayout.Toggle("Enabled", component.Enabled);
                        switch (component.ComponentType)
                        {
                            case (int)ColdTableComponentType.Rigidbody:
                                component.BodyType = EditorGUILayout.IntField("BodyType", component.BodyType);
                                component.Mass = EditorGUILayout.FloatField("Mass", component.Mass);
                                break;
                            case (int)ColdTableComponentType.Mesh:
                                component.MeshID = EditorGUILayout.TextField("MeshID", component.MeshID);
                                break;
                            case (int)ColdTableComponentType.Material:
                                component.MaterialID = EditorGUILayout.TextField("MaterialID", component.MaterialID);
                                break;

                        }
                    }
                }
                EditorGUI.indentLevel--;

            }
            EditorGUI.indentLevel--;
        }
            */

    }

    private ColdTableScene InterpretActiveScene()
    {
        Scene currentScene = SceneManager.GetActiveScene();
        List<GameObject> rootObjs = new List<GameObject>();
        currentScene.GetRootGameObjects(rootObjs);

        ColdTableScene output = new ColdTableScene();
        output.SceneName = currentScene.name;
        output.Objects = new List<ColdTableObject>();
        foreach (var obj in rootObjs)
        {
            ColdTableObject outputObj = new ColdTableObject();
            outputObj.Name = obj.name;
            outputObj.Enabled = obj.activeSelf;
            outputObj.Transform = new ColdTableTransform();
            outputObj.Transform.Position = obj.transform.position;
            outputObj.Transform.Scale = obj.transform.localScale;
            outputObj.Transform.Rotation = obj.transform.rotation;

            outputObj.Components = new();

            // Interpret Components

            if (obj.TryGetComponent<MeshFilter>(out var Mesh))
            {
                ColdTableComponentWrapper comp = new ColdTableComponentWrapper();
                comp.ComponentType = (int)ColdTableComponentType.Mesh;
                if (Mesh.sharedMesh == cubeMesh) { comp.MeshID = "Cube"; outputObj.Components.Add(comp); }
                if (Mesh.sharedMesh == planeMesh) { comp.MeshID = "Plane"; outputObj.Components.Add(comp); }
                if (Mesh.sharedMesh == cylinderMesh) { comp.MeshID = "Cylinder"; outputObj.Components.Add(comp); }
                if (Mesh.sharedMesh == capsuleMesh) { comp.MeshID = "Capsule"; outputObj.Components.Add(comp); }
                if (Mesh.sharedMesh == sphereMesh) { comp.MeshID = "Sphere"; outputObj.Components.Add(comp); }
            }

            if (obj.TryGetComponent<Rigidbody>(out var rb))
            {
                ColdTableComponentWrapper comp = new ColdTableComponentWrapper();
                comp.ComponentType = (int)ColdTableComponentType.Rigidbody;
                if(comp.Mass > 0.0001f)
                    comp.Mass = rb.mass;
                comp.BodyType = rb.isKinematic ? (int)ColdTableRigidbodyType.Kinematic : rb.constraints == RigidbodyConstraints.FreezeAll ? (int)ColdTableRigidbodyType.Static : (int)ColdTableRigidbodyType.Dynamic;
                outputObj.Components.Add(comp);
            }

            output.Objects.Add(outputObj);
        }

        return output;
    }

    private void WriteScene(ColdTableScene scene, bool autoload)
    {
        string filename = scene.SceneName + ".unity";
        string fullpath = sceneAssetPath + filename;

        if (File.Exists(fullpath))
        {
            AssetDatabase.DeleteAsset(fullpath);
            AssetDatabase.Refresh();
        }

        Scene newScene = EditorSceneManager.NewScene(NewSceneSetup.EmptyScene, NewSceneMode.Single);

        // Write Objects
        foreach (var obj in scene.Objects)
        {
            string meshID = "";
            string materialID = "";
            ColdTableRigidbodyType rbType = ColdTableRigidbodyType.None;
            float rbMass = 0.0f;

            foreach (var comp in obj.Components)
            {
                if (comp.ComponentType == (int)ColdTableComponentType.Mesh)
                    meshID = comp.MeshID;
                if (comp.ComponentType == (int)ColdTableComponentType.Material)
                    materialID = comp.MaterialID;
                if (comp.ComponentType == (int)ColdTableComponentType.Rigidbody)
                {
                    rbType = (ColdTableRigidbodyType)comp.BodyType;
                    rbMass = comp.Mass;
                    if (rbMass < 0.0001f) rbMass = 0.0001f;
                }
            }

            GameObject newObj = meshID switch
            {
                "Cube" => GameObject.CreatePrimitive(PrimitiveType.Cube),
                "Sphere" => GameObject.CreatePrimitive(PrimitiveType.Sphere),
                "Cylinder" => GameObject.CreatePrimitive(PrimitiveType.Cylinder),
                "Capsule" => GameObject.CreatePrimitive(PrimitiveType.Capsule),
                "Plane" => GameObject.CreatePrimitive(PrimitiveType.Plane),
                _ => new GameObject(),
            };

            newObj.name = obj.Name;
            newObj.SetActive(obj.Enabled);
            newObj.transform.SetPositionAndRotation(obj.Transform.Position, obj.Transform.Rotation);
            newObj.transform.localScale = obj.Transform.Scale;

            if (rbType != ColdTableRigidbodyType.None)
            {
                newObj.AddComponent<Rigidbody>();
                newObj.GetComponent<Rigidbody>().mass = rbMass;
                newObj.GetComponent<Rigidbody>().isKinematic = rbType == ColdTableRigidbodyType.Kinematic;
                newObj.GetComponent<Rigidbody>().useGravity = rbType == ColdTableRigidbodyType.Dynamic;
                newObj.GetComponent<Rigidbody>().constraints = rbType == ColdTableRigidbodyType.Static ? RigidbodyConstraints.FreezeAll : RigidbodyConstraints.None;

                if (newObj.GetComponent<MeshCollider>() == null)
                    newObj.AddComponent<MeshCollider>();
                newObj.GetComponent<MeshCollider>().convex = true;
            }
        }

        bool success = EditorSceneManager.SaveScene(newScene, fullpath);
        if (success && autoload) EditorSceneManager.OpenScene(fullpath);

        AssetDatabase.Refresh();
    }
    
    private static Mesh PrimitiveMesh(PrimitiveType type)
    {
        GameObject temp = GameObject.CreatePrimitive(type);
        Mesh mesh = temp.GetComponent<MeshFilter>().sharedMesh;
        Object.DestroyImmediate(temp);
        return mesh;
    }
}


