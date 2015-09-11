using UnityEngine;
using System.Collections;

public class TiledBackground : MonoBehaviour
{
    public int textureSize = 32;
    public bool xRepeat = true;
    public bool yRepeat = true;

    void Start()
    {
        var x_count = !xRepeat ? 1 : Mathf.Ceil(PixelPerfectCamera.resolution.x / textureSize);
        var y_count = !yRepeat ? 1 : Mathf.Ceil(PixelPerfectCamera.resolution.y / textureSize);

        transform.localScale = new Vector3(x_count * textureSize, y_count * textureSize, 1);

        GetComponent<Renderer>().material.mainTextureScale = new Vector3(x_count, y_count, 1);
    }

    void Update()
    {

    }
}
