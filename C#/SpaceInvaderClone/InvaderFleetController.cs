using System.Collections;
using System.Collections.Generic;
using System;
using UnityEngine;

// InvaderFleetController manages the main fleet of invaders
public class InvaderFleetController : MonoBehaviour
{
    // Reference to the main game controller
    [SerializeField] private GameController gameController = null;

    // Array of game object references to different invaders - 4 elements - one per level - it's a 4 level game :)
    // We'll leave as a collection (Array) of empty (null) references and add in Unity later
    [SerializeField] private GameObject[] invaderTypes = new GameObject[4] { null, null, null, null };
    
    // Size of the invader fleet and range it can move from side-to-side (set in Unity later)
    [SerializeField] private int numRows = 0;
    [SerializeField] private int numColumns = 0;
    [SerializeField] private float baseXMin = 0;
    [SerializeField] private float baseXMax = 0;

    // Speed to fleet movement
    [SerializeField] private float horizontalSpeed = 1.0f;

    // Current state of the fleet
    private float baseX;
    private EnemyDirection currentDirection;
    private int numInvaders;

    // Reference to laser game object that will be fired
    [SerializeField] private GameObject laserPrefab = null;

    // Time delay between invaders firing.  You might think each invader has control over this, since each invader might decide when to fire, but we want to be fair to the player and provide more control over when enemy invaders fire, so we'll control this at the fleet level, not in each individual invader game object.  We'll set the time delay in Unity (initialise to 1 second for now)
    [SerializeField] private float fireDelayTime = 1.0f;

    // Actual fire countdown
    private float fireTime;

    // C# random number generator - we'll use this when picking which invader will fire
    System.Random rndGen;

    // Start is called before the first frame update
    void Start()
    {
        // Create the random number object and call it rndGen.  No random numbers yet, but we're now ready to call on rndGen to get one when needed.
        rndGen = new System.Random();

        // Initialise the stating position of the fleet, and the number of invaders as the number of columns * the number of rows in the fleet
        baseX = baseXMin;
        numInvaders = numRows * numColumns;

        // Set the fleet to start moving left when the game starts
        currentDirection = EnemyDirection.Left;

        fireTime = fireDelayTime;
        
        // Call the generateFleet function to create the invader game objects
        generateFleet();
    }

    // Generate the invaders!
    public void generateFleet(int level=0)
    {
        // We use a loop (iteration) to do this - a for loop is a type of loop we use when we know the number of elements to process
        // So here we're processing 'numRows' (tracking which row we're working on in the y variable)...
        for (int y = 0; y < numRows; y++)
        {
            // ...and for each row we loop through each invader in the row.
            for (int x = 0; x < numColumns; x++)
            {
                int invaderTypeIndex;

                invaderTypeIndex = y % 2;
                // For each invader generate the invader game object
                GameObject invader = Instantiate(invaderTypes[level], new Vector2(baseX + (float)x, 4.0f - (float)y), Quaternion.identity, transform);

                // Get the FleetInvader component - this is the component / script we wrote for the invader...
                FleetInvader fi = invader.GetComponent<FleetInvader>();

                // and tell it that the fleet it belongs to is the current fleet game object.
                fi.assignToFleet(this);
            }
        }
    }

    // When an invader is hit, it tells the fleet it has been hit...
    public void invaderDestroyed(FleetInvader invader)
    {
        // ... first the fleet reduces the number of invaders stored
        numInvaders--;

        // ... then passes the number of points for the hit invader up to the main game controller (which will in turn tell the player to get the points!)
        gameController.updatePlayerScore(invader.getPointsValue());
    }

    // Update is called once per frame
    void Update()
    {
        // As with the player, we do two things - move fleet and handle firing
        // We've done divide and conquer here - move and fire in separate functions to help manage complexity!

        moveFleet();

        // Process enemy fire
        fireLaser();
    }

    void moveFleet()
    {
        // Initialise how much we want to move the fleet by to 0
        float dx = 0.0f;
        float dy = 0.0f;

        // Then based on the current direction and position, move the fleet left or right (we set dx and dy here)
        if (currentDirection == EnemyDirection.Left)
        {
            // On moving left, if we're at the left edge of the play area, don't move across just set the fleet to move down a bit
            // and change the direction to 'move right' for the next frame
            if (baseX <= baseXMin)
            {
                dy = -0.4f;
                currentDirection = EnemyDirection.Right;
            }
            else
            {
                // otherwise, if we're not at the left edge set the horizontal movement (dx) to be a negative value and no vertical movement (dy = 0)
                dx = -horizontalSpeed * Time.deltaTime; // - 0.0025f;
            }
        }
        else if (currentDirection == EnemyDirection.Right)
        {
            if (baseX >= baseXMax)
            {
                dy = -0.4f;
                currentDirection = EnemyDirection.Left;
            }
            else
            {
                dx = horizontalSpeed * Time.deltaTime; //0.0025f;
            }
        }

        // Move the fleet's x (horizontal) position
        baseX += dx;

        // The fleet game object is the parent of all the invader game objects (the invaders appear nested in the fleet when seen in Unity's Hierarchy view)
        // The function GetComponentsInChildren gives us all the current invaders as a collection (Array)
        FleetInvader[] invaderFleet = GetComponentsInChildren<FleetInvader>();

        // For each invader in the array, call it's moveInFleet function to move!
        foreach (FleetInvader invader in invaderFleet)
        {
            invader.moveInFleet(dx, dy);
        }
    }


    void fireLaser()
    {
        // Decrease the fire countdown
        fireTime -= Time.deltaTime;

        // Similar logic to the player's fire but no keypress checked!
        // If the fire countdown reaches (or passes) 0 we can fire
        if (fireTime <= 0.0f)
        {
            // Pick a random invader to fire (if there are any - childCount tells us how many invaders are left).
            // Confession:  This class has REDUNDANCY - the numInvaders variable does the same job as childCount - we've got two values tracking the same thing so we can actually safely remove numInvaders if we want :)
            if (transform.childCount > 0)
            {
                // Invaders are indexed 0 to number_of_invaders - 1.   Pick a random one...
                var invaderIndex = rndGen.Next(transform.childCount);

                // ...get the invader game object...
                GameObject obj = transform.GetChild(invaderIndex).gameObject;

                // ...and from the invader game object get the FleetInvader component (with our custom functions in)
                FleetInvader invader = obj.GetComponent<FleetInvader>();

                // Call fire so the invader fires a laser
                invader.fire(laserPrefab);

                // If an audio source is attached play the sound
                AudioSource audio = GetComponent<AudioSource>();
                if (audio)
                {
                    audio.Play();
                }
            }

            // Once fired, reset the fire countdown variable
            fireTime = fireDelayTime;
        }
    }

    // Return the number of invaders left in the fleet (used by the game controller to determine that we need to advance to the next level or end the game if there are 0 invaders left)
    public int numberOfInvaders()
    {
        return transform.childCount;
    }
}
