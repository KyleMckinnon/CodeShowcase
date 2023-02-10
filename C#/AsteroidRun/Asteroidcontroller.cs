using System.Collections;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Security.Cryptography;
using System.Threading;
using UnityEngine;

public class Asteroidcontroller : MonoBehaviour
{
    [SerializeField] private Animator animator = null;

    [SerializeField] private int points = 10;

    private GameController hostGameController = null;

    [SerializeField] private float moveSpeed = 1.0f;

    //[SerializeField] private float rotationSpeed = 90.0f;
    
    public int Points
    {
        get { return points; }
    }

    

    public GameController HostGameController
    {
        get { return hostGameController; }
        set { hostGameController = value; }
    }

    void OnTriggerEnter2D(Collider2D collision)
    {
        
        if (collision.gameObject.tag == "bullet") 
        {
            UnityEngine.Debug.Log("bullet hit");

            if (animator)
            {
                 
                animator.SetBool("isAlive", false);
                Destroy(transform.GetChild(0).gameObject);
            }
            
           

            Destroy(collision.gameObject);
        }
    }

    public void destroyAsteroid ()
    {
        if (hostGameController)
        hostGameController.updatePlayerScore(points);

        Destroy(gameObject);

    }

    // Start is called before the first frame update

    void Start()

    {

    }

    // Update is called once per frame

    void Update()

    {
        if (transform.position.x < -11.0f)
        {
            Destroy(gameObject);
        }
        if (transform.position.y > 8.0f)
        {
            Destroy(gameObject);
        }

        //transform.Rotate(0.0f, 0.0f, rotationSpeed * Time.deltaTime);

        transform.Translate(Vector2.left * moveSpeed * Time.deltaTime, Space.World);

    }

    
}
