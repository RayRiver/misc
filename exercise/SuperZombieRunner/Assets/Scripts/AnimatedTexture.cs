using UnityEngine;
using System.Collections;

public class AnimatedTexture : MonoBehaviour
{
    public Vector2 velocity = Vector2.zero;

    private Material material;
    private Vector2 offset = Vector2.zero;

    void Start()
    {
        material = GetComponent<Renderer>().material;
        offset = material.GetTextureOffset("_MainTex");
    }

    void Update()
    {
        offset += velocity * Time.deltaTime;
        material.SetTextureOffset("_MainTex", offset);
    }
}
