using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// LeftPath is added to the boss enemy at runtime so it moves from right to left across the screen.
public class LeftPath : MonoBehaviour
{
    // speed determines how many units (in world coordinate space) the boss moves in 1 second
    // Adding the [SerializeField] attribute allows us to see and change this from Unity's Inspector tab.
    // Note:  could just say public float speed = 4, but good practice is to make all data private in a class.
    [SerializeField] private float speed = 4.0f;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        // Translate (move) the boss enemy - the direction is left and the amount depends on speed and elapsed time.
        // ALL animations should factor in time for consistency across different hardware!!!
        transform.Translate(Vector2.left * speed * Time.deltaTime);

        // checkEndOfLife is a function that check's the boss's position and removed it from the scene when it reaches the left edge of the screen.
        // (see below for the implementation of checkEndOfLife)
        checkEndOfLife();
    }

    void checkEndOfLife()
    {
        // If the boss's x position is less than or equal to -8 then remove it from the scene by calling Destroy.
        if (transform.position.x <= -8.0f)
        {
            // gameObject is a reference to the boss game object - not just any one component within the game object.
            // Passing gameObject to the Destroy function removed the entire boss object, not just any one component.
            Destroy(gameObject);
        }
    }
}
