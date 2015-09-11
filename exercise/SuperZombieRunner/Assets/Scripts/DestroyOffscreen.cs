using UnityEngine;
using System.Collections;

public class DestroyOffscreen : MonoBehaviour
{
    private Rigidbody2D body2d;
    private float offset = 100f;
    private float screenBorderX = 0f;
    private float screenBorderY = 0f;

    void Awake()
    {
        body2d = GetComponent<Rigidbody2D>();
    }

    void Start()
    {
        screenBorderX = PixelPerfectCamera.resolution.x / 2 + offset;
        screenBorderY = PixelPerfectCamera.resolution.y / 2 + offset;
    }

    void Update()
    {
        var posX = transform.position.x;
        var posY = transform.position.y;
        var dirX = body2d.velocity.x;
        var dirY = body2d.velocity.y;

        bool offscreen = false;
        if (posX < -screenBorderX && dirX < 0)
        {
            offscreen = true;
        }
        else if (posX > screenBorderX && dirX > 0)
        {
            offscreen = true;
        }
        else if (posY < -screenBorderY && dirY < 0)
        {
            offscreen = true;
        }
        else if (posY > screenBorderY && dirY > 0)
        {
            offscreen = true;
        }

        if (offscreen)
        {
            Destroy(gameObject);
        }
    }
}
