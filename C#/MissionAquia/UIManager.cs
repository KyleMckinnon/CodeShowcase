using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UIManager : MonoBehaviour
{


	// Use this for initialization
	void Start()
	{
		Time.timeScale = 1;
		pauseObjects = GameObject.FindGameObjectsWithTag("ShowOnPause");
		hideObjects = GameObject.FindGameObjectsWithTag("HideOnPause");
		hidePaused();
	}

	// Update is called once per frame
	void Update()
	{

		//uses the Escape button to pause and unpause the game
		if (Input.GetKeyDown(KeyCode.Escape))
		{


			if (Time.timeScale == 1)
			{

				Time.timeScale = 0;
				showPaused();
			}
			else if (Time.timeScale == 0)
			{
				Time.timeScale = 1;
				hidePaused();
			}
		}
	}
	//Closes the game
	GameObject[] pauseObjects;
	GameObject[] hideObjects;

	public void doExitGame()
	{
		Application.Quit();
	}

	//Reloads the Level
	public void Reload()
	{
		Application.LoadLevel(Application.loadedLevel);
	}

	//controls the pausing of the scene
	public void pauseControl()
	{
		if (Time.timeScale == 1)
		{
			Time.timeScale = 0;
			showPaused();
		}
		else if (Time.timeScale == 0)
		{
			Time.timeScale = 1;
			hidePaused();
		}
	}

	//shows objects with ShowOnPause tag
	public void showPaused()
	{
		foreach (GameObject g in pauseObjects)
		{
			g.SetActive(true);
		}

		foreach (GameObject g in hideObjects)
		{
			g.SetActive(false);
		}
	}

	//hides objects with ShowOnPause tag
	public void hidePaused()
	{
		foreach (GameObject g in pauseObjects)
		{
			g.SetActive(false);
		}

		foreach (GameObject g in hideObjects)
		{
			g.SetActive(true);
		}
	}

	//loads inputted level
	public void LoadLevel(string level)
	{
		Application.LoadLevel(level);
	}
}
