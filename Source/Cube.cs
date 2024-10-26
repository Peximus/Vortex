using UnityEngine;
using System.Collections.Generic;

public class Cube : MonoBehaviour
{

    float speed = 1.0f;

    float height = 1.0f;

    float game = 1.0f;

    float space = -8.0f;

    public float xAngle, yAngle, zAngle;

    private Vector3 scaleChange;

    private Vector3 location;

    private GameObject gameobject;

    public GameObject cylinder;

    private List<GameObject> list;

    void Awake()
    {

        scaleChange = new Vector3(0.0f, -0.01f, 0.0f);


    }


    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {

        //Instantiate(gameobject, new Vector3(0, 0, 0), Quaternion.identity);
        //gameobject = GameObject.CreatePrimitive(PrimitiveType.Cylinder);
        list = new List<GameObject>();


        for (float i = 0; i < 10; i++)
        {

            GameObject cube = GameObject.CreatePrimitive(PrimitiveType.Cube);
            
            cube.transform.position = new Vector3(space, 0, 0);

            scaleChange = new Vector3(-0.5f, -0.5f, -0.5f);

            cube.transform.localScale += scaleChange;

            space += 0.5f;

            //location = new Vector3(Random.Range(-10.0f, 10.0f), 0, Random.Range(-10.0f, 10.0f));

            //gameobject = Instantiate(cylinder, location, Quaternion.identity) as GameObject;

            list.Add(cube);

        }

    }

    // Update is called once per frame
    void Update()
    {

        space = -8.0f;

        game = 1.0f;

        //gameobject.transform.Rotate(xAngle, yAngle, zAngle, Space.Self);
        foreach (var cyl in list)
        {

            Vector3 pos = transform.position;

            Vector3 origin = new Vector3(0, 0, 0);

            float newY = Mathf.Sin((Time.time + game) * speed);

            cyl.transform.position = new Vector3(space, newY * height, pos.z);

            game += 0.1f;

            space += 0.5f;

        }


    }
}
