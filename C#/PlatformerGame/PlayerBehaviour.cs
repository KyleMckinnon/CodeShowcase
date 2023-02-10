using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerBehaviour : MonoBehaviour
{
    //reference to players rigidbody
    private Rigidbody rigidBody;

    //Force when player jumps
    public Vector2 jumpForce = new Vector2(0, 450);

    //Player movement speed on X axis
    public float maxSpeed = 3.0f;

    public float speed = 50.0f;

    private float xMove;

    private bool shouldJump;

    private bool onGround;
    private float yPrevious;

    private bool collidingWall;

    // Start is called before the first frame update
    void Start()
    {
        rigidBody = GetComponent<Rigidbody>();
        shouldJump = false;
        xMove = 0.0f;
        onGround = false;
        yPrevious = Mathf.Floor(transform.position.y);
        collidingWall = false;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        Movement();

        Camera.main.transform.position = new Vector3(transform.position.x, transform.position.y, Camera.main.transform.position.z);
    }

    void Update()
    {

        CheckGrounded();
        Jumping();
        
    }

    void Movement()
    {
        xMove = Input.GetAxis("Horizontal");

        if (collidingWall && !onGround)
        {
            xMove = 0;
        }
        if(xMove != 0)
        {
            float xSpeed = Mathf.Abs(xMove * rigidBody.velocity.x);

            if (xSpeed < maxSpeed)
            {
                Vector3 movementForce = new Vector3(1, 0, 0);
                movementForce *= xMove * speed;

                RaycastHit hit;
                if(!rigidBody.SweepTest(movementForce, out hit, 0.05f))
                {

                    rigidBody.AddForce(movementForce);

                }
                
            }

            if(Mathf.Abs(rigidBody.velocity.x) > maxSpeed)
            {
                Vector2 newVelocity;

                newVelocity.x = Mathf.Sign(rigidBody.velocity.x) * maxSpeed;
                newVelocity.y = rigidBody.velocity.y;

                rigidBody.velocity = newVelocity;
            }
        }

        else
        {
            Vector2 newVelocity = rigidBody.velocity;

            newVelocity.x *= 0.9f;
            rigidBody.velocity = newVelocity;
        }
    }

    void Jumping()
    {
        if(Input.GetButtonDown("Jump"))
        {
            shouldJump = true;
        }

        if(shouldJump && onGround)
        {
            rigidBody.AddForce(jumpForce);
            shouldJump = false;
        }
    }

    void CheckGrounded()
    {
        float distance = (GetComponent<CapsuleCollider>().height / 2 * this.transform.localScale.y) + .01f;
        Vector3 floorDirection = transform.TransformDirection(-Vector3.up);
        Vector3 origin = transform.position;

        if(!onGround)
        {
            if(Physics.Raycast(origin, floorDirection, distance))
            {
                onGround = true;
            }
        }

        else if ((Mathf.Floor(transform.position.y) != yPrevious))
        {
            onGround = false;
        }

        yPrevious = Mathf.Floor(transform.position.y);
    }

    void OnCollisionStay(Collision collision)
    {
        if(!onGround)
        {
            collidingWall = true;
        }
    }

    void OnCollisionExit(Collision collision)
    {
        collidingWall = false;
    }

    //void OnDrawGizmos()
    //{
    //    Debug.DrawLine(transform.position, transform.position + rigidBody.velocity, Color.red);
    //}
}
