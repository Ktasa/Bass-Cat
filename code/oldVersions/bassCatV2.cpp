/* updates animation based on time value

	bool F1 = true;
	bool hitThatBass = false;
	int inputTimeOut = 0;
	int hitFrame = 1;
	Sprite current;
	int frameID = 1;
	bool boost = false;

	while (window.isOpen())
	{
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			current = spriteC;
			window.clear(Color::White);
			window.draw(current);
			window.display();

			window.close();
		}
		if ( (Keyboard::isKeyPressed(Keyboard::Space)) && inputTimeOut==0 && hitFrame == 1)
		{
			hitThatBass = true;
			clock.restart(); //reset timing of animation
		}
		if (!Keyboard::isKeyPressed(Keyboard::Space))
		{
			//inputTimeOut = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::LShift))
		{
			boost = true;
		}
		if (!Keyboard::isKeyPressed(Keyboard::LShift))
		{
			boost = false;
		}
		if (timeCount > update && !hitThatBass)
		{
			F1 = !F1;
			if (F1)
				frameID = 1;
			else
				frameID = 2;

			timeCount -= update;
            if(inputTimeOut > 0){inputTimeOut--;}
		}
		if(hitThatBass && inputTimeOut==0 && timeCount > updateTest && !boost)
		{
            F1 = !F1;
			if (F1)
				frameID = 3;
			else
				frameID = 4;

			if (hitFrame == 1)
            {
                if(bass.getStatus() == bass.Playing)
                    bass.stop();
            	bass.play();
                
                hitFrame++;
            }
            else
            {
				inputTimeOut = 2;
				hitThatBass = false;
				hitFrame = 1;
			}
			timeCount -= update;
		}
		if(hitThatBass && boost && timeCount > updateTest)
		{
			F1 = !F1;
			if(F1)
				frameID = 1;
			else
				frameID = 4;

			timeCount -= update;
		}
		current = bassCat.getSprite(frameID);
		window.clear(Color::White);
		window.draw(current);
		window.display();

        dt = clock.restart();
        timeCount += dt.asSeconds();
        //if(timeCount > update)
        //{
            //cout << timeCount << endl;
        //}
	}
		*/