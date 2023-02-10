using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// Simple component (script) to control the behaviour of an enemy laser
public class LaserBlastBehaviour : MonoBehaviour
{
    // How far (per second) lasers travel in world coordinates - we can set in Unity as well!
    [SerializeField] private float speed = 3.0f;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        // Translate (move) the laser down the screen
        transform.Translate(Vector2.down * speed * Time.deltaTime);
        
        // If we're outside the play area remove the laser from the scene
        if (transform.position.y < -5.0f)
        {
            Destroy(gameObject);
        }

    }
}
