using UnityEngine;
using System.Collections;

public class Spawner : MonoBehaviour
{
    public GameObject[] prefabs;
    public float delay = 2f;
    public bool active = true;

    void Start()
    {
        StartCoroutine(ItemGenerator());
    }

    IEnumerator ItemGenerator()
    {
        yield return new WaitForSeconds(delay);

        if (active)
        {
            Instantiate(prefabs[Random.Range(0, prefabs.Length)], transform.position, Quaternion.identity);
        }

        StartCoroutine(ItemGenerator());
    }

    void Update()
    {

    }
}
