using System.Collections;
using System.Collections.Generic;
using System;
using UnityEngine;

// BossGenerator is used as a component to control when a boss appears on the screen and randomly choose which direction (path) it should take.
// In Unity, the host game object isn't visible but is still part of the scene, and this component's update function gets called every frame to determine when a new boss is needed.
public class BossGenerator : MonoBehaviour
{
    // Prefab reference to boss
    [SerializeField] private GameObject bossPrefab = null;


    // Seconds between boss spawn (we can set this in Unity)
    [SerializeField] private float spawnTime = 0.0f;

    // Actual countdown to boss spawn
    private float spawnCountdown = 0.0f;

    // C# random number generator (we'll pick a random number for chosing left or right moving boss)
    System.Random rndGen;

    // Start is called before the first frame update
    void Start()
    {
        // Create the random number object and call it rndGen.  No random numbers yet, but we're now ready to call on rndGen to get one when needed.
        rndGen = new System.Random();

        // Reset out countdomn timer.
        spawnCountdown = spawnTime;
    }

    // Update is called once per frame
    void Update()
    {
        // Decrease our countdown timer based on elapsed time.
        spawnCountdown -= Time.deltaTime;

        // When we reach zero, or pass zero since our counter may not decrease to EXACTLY zero :)...
        if (spawnCountdown <= 0.0f)
        {

            // Generate boss...
            
            // Pick a random number between 0 and 1 (2 is not included) - if it's a 0 we setup a left moving boss...
            if (rndGen.Next(2)==0)
            {
                // First create the boss game object (which also contains the BossController)
                GameObject invader = Instantiate(bossPrefab, new Vector2(8.0f, 4.5f), Quaternion.identity);

                // Then add a LeftPath component to the boss to handle movement
                invader.AddComponent(typeof(LeftPath));
            }
            else
            {
                // ...otherwise it must be a 1 so we setup a right moving boss

                // First create the boss game object (which also contains the BossController)
                GameObject invader = Instantiate(bossPrefab, new Vector2(-8.0f, 4.5f), Quaternion.identity);

                // Then add a RightPath component to the boss to handle movement
                invader.AddComponent(typeof(RightPath));
            }

            // What we have at this point is a new boss, but depending on the random number selection, we have one of two possibilities...
            // either boss with a LeftPath or boss with a RightPath
            // This is something we can ONLY do in the script - not in Unity's editor itself!
            
            // Reset countdown timer ready for the next boss!
            spawnCountdown = spawnTime;
        }
    }
}
