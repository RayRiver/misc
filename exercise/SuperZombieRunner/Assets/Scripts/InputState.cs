using UnityEngine;
using System;
using System.Collections;

public class InputState : MonoBehaviour
{
    //public bool touchGround = false;
    //public bool actionButton = false;

    private Rigidbody2D body2d;
    private Animator animator;

    private float touchGroundThreshold = 1f;
    private float jumpSpeed = 250f;
    private float forwardSpeed = 20f;

    void Awake()
    {
        body2d = GetComponent<Rigidbody2D>();
        animator = GetComponent<Animator>();
    }

    void Update()
    {
        var actionButton = Input.anyKeyDown;

        var absVx = Math.Abs(body2d.velocity.x); 
        var absVy = Math.Abs(body2d.velocity.y);
        var touchGround = absVy <= touchGroundThreshold;

        if (touchGround)
        {
            if (actionButton)
            {
                body2d.velocity = new Vector2(transform.position.x < 0 ? forwardSpeed : 0, jumpSpeed);
            }
        }

        var running = true;
        if (absVx > 0 && touchGround)
        {
            running = false;
        }

        animator.SetBool("Running", running);
    }

    void FixedUpdate()
    {
        //var absVx = Math.Abs(body2d.velocity.x); 
        //var absVy = Math.Abs(body2d.velocity.y);
        //touchGround = absVy <= touchGroundThreshold;
    }
}
