using System.Collections;
using System.Collections.Generic;
using System.Threading;
using UnityEngine;

// Simple component (script) to control the behaviour of a player's bullet
public class SimpleBulletBehaviour : MonoBehaviour
{
    // How far (per second) bullets travel in world coordinates - we can set in Unity as well!
    [SerializeField] private float speed = 3.0f;

    // Reference to the player who fired the bullet
    private HPlayerController owner;

    // Property to store and access the player who fired the bullet
    public HPlayerController OwningPlayer
    {
        get { return owner; }
        set { owner = value; }
    }

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        // Move the bullet up the screen
        transform.Translate(Vector2.up * speed * Time.deltaTime);

        // If the bullet reaches the top of the play area remove it from the scene
        if (transform.position.y > 5.0f)
        {
            Destroy(gameObject);
        }
    }
}
