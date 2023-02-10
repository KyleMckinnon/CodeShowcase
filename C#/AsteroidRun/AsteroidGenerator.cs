using System.Collections;
using System.Collections.Generic;
using System;
using UnityEngine;

public class AsteroidGenerator : MonoBehaviour
{
    [SerializeField] private GameController hostGameController = null;

    [SerializeField] private GameObject[] asteroidTypes = new GameObject[4] { null, null, null, null };

    [SerializeField] private float asteroidSpawnTime = 1.0f;

    private float countdown = 0.0f;

    System.Random rndGen;



    // Start is called before the first frame update

    void Start()

    {

        rndGen = new System.Random();

    }

    // Update is called once per frame

    void Update()

    {

        countdown -= Time.deltaTime;

        if (countdown <= 0.0f)

        {

            generateAsteroid();

            countdown = asteroidSpawnTime;

        }

    }

    void generateAsteroid()

    {

        int typeIndex = rndGen.Next(4);

        GameObject asteroid = Instantiate(asteroidTypes[typeIndex], new Vector2(10.0f, (float)(rndGen.Next(10) - 5)), Quaternion.identity);

        // Instantiate returns the game object reference - that is, a reference to the container of components so
        // we ask for the specific component which will store the asteroids game controller reference.
        var AsteroidcontrollerComponent = asteroid.GetComponent<Asteroidcontroller>();

        // Set the reference via the property defined on the AsteroidController
        AsteroidcontrollerComponent.HostGameController = this.hostGameController;


    }

}
