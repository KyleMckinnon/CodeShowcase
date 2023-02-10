using System.Collections;
using System.Collections.Generic;
using System.Threading;
using UnityEngine;

// enum types allow us to model a selection of possible values - here we have enemy direction (left or right)
public enum EnemyDirection
{
    Left,
    Right
}

// Describe the behaviour of a single enemy invader
public class Enemy : MonoBehaviour
{
    // The current direction the enemy invader is moving in - start off going right, but we can change later
    [SerializeField] private EnemyDirection currentDirection = EnemyDirection.Right;

    // The enemy moves within the bounds of the play area - so we need to know about the play area.  Set to null (no play area) for now, but we can change this in Unity when the play area game object has been setup.
    [SerializeField] private PlayArea playArea = null;



    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        // If the invader is moving left, update left...
        if (currentDirection==EnemyDirection.Left)
        {
            // Translate (move) the invader left by the specified speed
            // note: transform refers to the Transform component the invader's game object has.
            transform.Translate(Vector2.left * 1.0f * Time.deltaTime);

            // If we've moved past the left edge of the play area, move the invader down and tell it to change direction
            // so next frame update it will move right...
            if (transform.position.x < playArea.transform.position.x - playArea.getWidth() / 2.0)
            {
                // Move 0.1f on the y axis (that is, move down the play area)
                transform.Translate(0, -0.1f, 0);

                // ...and set our current direction to move right
                currentDirection = EnemyDirection.Right;
            }

        }
        else if (currentDirection == EnemyDirection.Right)
        {
            // On the other hand, if we're moving right during the current frame, translate right...
            transform.Translate(Vector2.right * 1.0f * Time.deltaTime);

            // If we've moved past the right edge of the play area, move the invader down and tell it to change direction
            // so next frame update it will move left...
            if (transform.position.x > playArea.transform.position.x + playArea.getWidth() / 2.0)
            {
                transform.Translate(0, -0.1f, 0);
                currentDirection = EnemyDirection.Left;
            }
        }
    }
}
