//  Memory Game
//  CS 335 001    Date:  9/20/2013
//  Nicholas Hollis
//  
//  This code is for a memory game that lets the user flip over two cards.
//  If these cards are a match, then the cards stay flipped over.  If they are not,
//  the cards will flip back over after a few seconds and wait for another pair.
//  The game is over when all cards are matched.
package com.example.memorygame;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
//import android.view.View.OnClickListener;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Random;
import java.util.Timer;
import java.util.TimerTask;
import java.lang.Integer;
import android.widget.TextView;
import android.os.SystemClock;
import android.widget.Chronometer;



public class MainActivity extends Activity {
	private int flip_count;  //keep track of how many cards are flipped

	private Integer[] deck = {R.drawable.bobafet, R.drawable.c3po, R.drawable.chewbacca, 
			R.drawable.darthvader,R.drawable.hansolo, R.drawable.leia, R.drawable.luke, 
			R.drawable.obiwan, R.drawable.r2d2, R.drawable.yoda, R.drawable.bobafet, 
			R.drawable.c3po, R.drawable.chewbacca, R.drawable.darthvader,R.drawable.hansolo, 
			R.drawable.leia, R.drawable.luke, R.drawable.obiwan, R.drawable.r2d2, R.drawable.yoda};

	public boolean[] matched = new boolean[20];
	public Integer ImgOne;
	public Integer ImgTwo;
	public ImageButton cardOne;
	public ImageButton cardTwo;
	//private Timer gameTimer;
	private Timer myTimer;
	//private Handler gameHandler;
	private CustomHandler myHandler;
	public Integer matchCard1;
	public boolean match = false;
	Chronometer mChronometer;
	int num_matched = 0;
	
	class CustomTimerTask extends TimerTask {
		 
        @Override
        public void run() {
            myHandler.sendEmptyMessage(0);
            //mImgButton.setImageResource(R.drawable.ic_launcher);
        }
    }

       class CustomHandler extends Handler{

    @Override
    public void handleMessage(Message msg) {
            super.handleMessage(msg);
            /// Do your listview update thing
            //Log.d(TAG, "handler call back");  
//            mImgButton.setImageResource(R.drawable.ic_launcher);
            cardOne.setImageResource(R.drawable.starwars);
			cardTwo.setImageResource(R.drawable.starwars);
			cardOne.setClickable(true);
			cardTwo.setClickable(true);
            myTimer.cancel();
            myTimer= null; 
            flip_count = 0;
        }
    }
	   
       
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		final ImageButton card1 = (ImageButton)findViewById(R.id.card1);
		final ImageButton card2 = (ImageButton)findViewById(R.id.card2);
		final ImageButton card3 = (ImageButton)findViewById(R.id.card3);
		final ImageButton card4 = (ImageButton)findViewById(R.id.card4);
		final ImageButton card5 = (ImageButton)findViewById(R.id.card5);
		final ImageButton card6 = (ImageButton)findViewById(R.id.card6);
		final ImageButton card7 = (ImageButton)findViewById(R.id.card7);
		final ImageButton card8 = (ImageButton)findViewById(R.id.card8);
		final ImageButton card9 = (ImageButton)findViewById(R.id.card9);
		final ImageButton card10 = (ImageButton)findViewById(R.id.card10);
		final ImageButton card11 = (ImageButton)findViewById(R.id.card11);
		final ImageButton card12 = (ImageButton)findViewById(R.id.card12);
		final ImageButton card13 = (ImageButton)findViewById(R.id.card13);
		final ImageButton card14 = (ImageButton)findViewById(R.id.card14);
		final ImageButton card15 = (ImageButton)findViewById(R.id.card15);
		final ImageButton card16 = (ImageButton)findViewById(R.id.card16);
		final ImageButton card17 = (ImageButton)findViewById(R.id.card17);
		final ImageButton card18 = (ImageButton)findViewById(R.id.card18);
		final ImageButton card19 = (ImageButton)findViewById(R.id.card19);
		final ImageButton card20 = (ImageButton)findViewById(R.id.card20);
		final Button resetButton = (Button)findViewById(R.id.reset_button);
		final Button startButton = (Button)findViewById(R.id.start_button);
		mChronometer = (Chronometer) findViewById(R.id.chronometer);
		assignToGrid();
		flip_count= 0;
		
		myHandler = new CustomHandler();
		
		for(int i=0; i<20; i++)	//used for set up of each game only
			matched[i] = false;

		card1.setImageResource(R.drawable.starwars);
		card2.setImageResource(R.drawable.starwars);
		card3.setImageResource(R.drawable.starwars);
		card4.setImageResource(R.drawable.starwars);
		card5.setImageResource(R.drawable.starwars);
		card6.setImageResource(R.drawable.starwars);
		card7.setImageResource(R.drawable.starwars);
		card8.setImageResource(R.drawable.starwars);
		card9.setImageResource(R.drawable.starwars);
		card10.setImageResource(R.drawable.starwars);
		card11.setImageResource(R.drawable.starwars);
		card12.setImageResource(R.drawable.starwars);
		card13.setImageResource(R.drawable.starwars);
		card14.setImageResource(R.drawable.starwars);
		card15.setImageResource(R.drawable.starwars);
		card16.setImageResource(R.drawable.starwars);
		card17.setImageResource(R.drawable.starwars);
		card18.setImageResource(R.drawable.starwars);
		card19.setImageResource(R.drawable.starwars);
		card20.setImageResource(R.drawable.starwars);
		
		card1.setClickable(false);
		card2.setClickable(false);
		card3.setClickable(false);
		card4.setClickable(false);
		card5.setClickable(false);
		card6.setClickable(false);
		card7.setClickable(false);
		card8.setClickable(false);
		card9.setClickable(false);
		card10.setClickable(false);
		card11.setClickable(false);
		card12.setClickable(false);
		card13.setClickable(false);
		card14.setClickable(false);
		card15.setClickable(false);
		card16.setClickable(false);
		card17.setClickable(false);
		card18.setClickable(false);
		card19.setClickable(false);
		card20.setClickable(false);
		resetButton.setClickable(false);
		
		card1.setOnClickListener(new View.OnClickListener() {
	        @Override
	        public void onClick(View v) {
	        	cardFlipped(card1, deck[0], 0);
	        }
	    });
		
		card2.setOnClickListener(new View.OnClickListener() {
	        @Override
	        public void onClick(View v) {
	        	cardFlipped(card2, deck[1], 1);
	        }
	    });
		
		card3.setOnClickListener(new View.OnClickListener() {
	        @Override
	        public void onClick(View v) {
	        	cardFlipped(card3, deck[2], 2);
	        }
	    });
		
		card4.setOnClickListener(new View.OnClickListener() {
	        @Override
	        public void onClick(View v) {
	        	cardFlipped(card4, deck[3], 3);
	        }
	    });
		
		card5.setOnClickListener(new View.OnClickListener() {
	        @Override
	        public void onClick(View v) {
	        	cardFlipped(card5, deck[4], 4);
	        }
	    });
		
		card6.setOnClickListener(new View.OnClickListener() {
	        @Override
	        public void onClick(View v) {
	        	cardFlipped(card6, deck[5], 5);
	        }
	    });
		
		card7.setOnClickListener(new View.OnClickListener() {
	        @Override
	        public void onClick(View v) {
	        	cardFlipped(card7, deck[6], 6);
	        }
	    });
		
		card8.setOnClickListener(new View.OnClickListener() {
	        @Override
	        public void onClick(View v) {
	        	cardFlipped(card8, deck[7], 7);
	        }
	    });
		
		card9.setOnClickListener(new View.OnClickListener() {
	        @Override
	        public void onClick(View v) {
	        	cardFlipped(card9, deck[8], 8);
	        }
	    });
		
		card10.setOnClickListener(new View.OnClickListener() {
	        @Override
	        public void onClick(View v) {
	        	cardFlipped(card10, deck[9], 9);
	        }
	    });
		
		card11.setOnClickListener(new View.OnClickListener() {
	        @Override
	        public void onClick(View v) {
	        	cardFlipped(card11, deck[10], 10);
	        }
	    });
		
		card12.setOnClickListener(new View.OnClickListener() {
	        @Override
	        public void onClick(View v) {
	        	cardFlipped(card12, deck[11], 11);
	        }
	    });
		
		card13.setOnClickListener(new View.OnClickListener() {
	        @Override
	        public void onClick(View v) {
	        	cardFlipped(card13, deck[12], 12);
	        }
	    });
		
		card14.setOnClickListener(new View.OnClickListener() {
	        @Override
	        public void onClick(View v) {
	        	cardFlipped(card14, deck[13], 13);
	        }
	    });
		
		card15.setOnClickListener(new View.OnClickListener() {
	        @Override
	        public void onClick(View v) {
	        	cardFlipped(card15, deck[14], 14);
	        }
	    });
		
		card16.setOnClickListener(new View.OnClickListener() {
	        @Override
	        public void onClick(View v) {
	        	cardFlipped(card16, deck[15], 15);
	        }
	    });
		
		card17.setOnClickListener(new View.OnClickListener() {
	        @Override
	        public void onClick(View v) {
	        	cardFlipped(card17, deck[16], 16);
	        }
	    });
		
		card18.setOnClickListener(new View.OnClickListener() {
	        @Override
	        public void onClick(View v) {
	        	cardFlipped(card18, deck[17], 17);
	        }
	    });
		
		card19.setOnClickListener(new View.OnClickListener() {
	        @Override
	        public void onClick(View v) {
	        	cardFlipped(card19, deck[18], 18);
	        }
	    });
		
		card20.setOnClickListener(new View.OnClickListener() {
	        @Override
	        public void onClick(View v) {
	        	cardFlipped(card20, deck[19], 19);
	        }
	    });
	
		startButton.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				card1.setClickable(true);
				card2.setClickable(true);
				card3.setClickable(true);
				card4.setClickable(true);
				card5.setClickable(true);
				card6.setClickable(true);
				card7.setClickable(true);
				card8.setClickable(true);
				card9.setClickable(true);
				card10.setClickable(true);
				card11.setClickable(true);
				card12.setClickable(true);
				card13.setClickable(true);
				card14.setClickable(true);
				card15.setClickable(true);
				card16.setClickable(true);
				card17.setClickable(true);
				card18.setClickable(true);
				card19.setClickable(true);
				card20.setClickable(true);
				resetButton.setClickable(true);
				startButton.setClickable(false);
				mChronometer.start();
			}
		});
		
		resetButton.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				card1.setImageResource(R.drawable.starwars);
				card2.setImageResource(R.drawable.starwars);
				card3.setImageResource(R.drawable.starwars);
				card4.setImageResource(R.drawable.starwars);
				card5.setImageResource(R.drawable.starwars);
				card6.setImageResource(R.drawable.starwars);
				card7.setImageResource(R.drawable.starwars);
				card8.setImageResource(R.drawable.starwars);
				card9.setImageResource(R.drawable.starwars);
				card10.setImageResource(R.drawable.starwars);
				card11.setImageResource(R.drawable.starwars);
				card12.setImageResource(R.drawable.starwars);
				card13.setImageResource(R.drawable.starwars);
				card14.setImageResource(R.drawable.starwars);
				card15.setImageResource(R.drawable.starwars);
				card16.setImageResource(R.drawable.starwars);
				card17.setImageResource(R.drawable.starwars);
				card18.setImageResource(R.drawable.starwars);
				card19.setImageResource(R.drawable.starwars);
				card20.setImageResource(R.drawable.starwars);
				card1.setClickable(false);
				card2.setClickable(false);
				card3.setClickable(false);
				card4.setClickable(false);
				card5.setClickable(false);
				card6.setClickable(false);
				card7.setClickable(false);
				card8.setClickable(false);
				card9.setClickable(false);
				card10.setClickable(false);
				card11.setClickable(false);
				card12.setClickable(false);
				card13.setClickable(false);
				card14.setClickable(false);
				card15.setClickable(false);
				card16.setClickable(false);
				card17.setClickable(false);
				card18.setClickable(false);
				card19.setClickable(false);
				card20.setClickable(false);
				resetButton.setClickable(false);
				assignToGrid();
				flip_count= 0;
				mChronometer.setBase(SystemClock.elapsedRealtime());
				mChronometer.stop();
				startButton.setClickable(true);
			}
		});
	}
	
	
	
	public void assignToGrid() 
	{
		Collections.shuffle(Arrays.asList(deck));
	}
	
	
	public void cardFlipped(ImageButton card, Integer image, Integer c)
	{
			switch(flip_count) {
			case 0:			
				card.setImageResource(image);
				card.setClickable(false);
				flip_count++;
				ImgOne = image;
				cardOne = card;
				matchCard1 = c;
				break;
			case 1:
				match = false;
				flip_count++;
				card.setImageResource(image);
				card.setClickable(false);
				ImgTwo = image;
				cardTwo = card;
				match = checkMatch(ImgOne, ImgTwo);
				if(match) 
				{
					matched[matchCard1] = true;
					matched[c] = true;
					cardOne.setClickable(false);
					cardTwo.setClickable(false);
					flip_count = 0;
					num_matched++;
					if(num_matched >= 10)
					{
						mChronometer.stop();
					}
				}
				else
				{
					if (myTimer!= null) {
	    				myTimer.cancel();
	    				myTimer = null; 
	    			}
	    			
					myTimer = new Timer();
	    			CustomTimerTask customTimerTask = new CustomTimerTask();
	    			//customTimerTask.run();
	    			//timer.scheduleAtFixedRate(, 5000 , 1000);
	    			myTimer.schedule(customTimerTask, 3000);
				}
				break;
			case 2:
				if (myTimer!= null) {
    				myTimer.cancel();
    				myTimer = null; 
    			}
				cardOne.setImageResource(R.drawable.starwars);
				cardTwo.setImageResource(R.drawable.starwars);
				cardOne.setClickable(true);
				cardTwo.setClickable(true);
				card.setImageResource(image);
				card.setClickable(false);
				flip_count = 1;
				ImgOne = image;
				cardOne = card;
				matchCard1 = c;
				break;
			}
			return;					
	}
	
	public boolean checkMatch(Integer Image1, Integer Image2)
	{
		if (getResources().getDrawable(Image1).getConstantState().equals (getResources().getDrawable(Image2).getConstantState())) 
		{
			return true;
		}
		else
		{
			return false;
		}
	}

}
