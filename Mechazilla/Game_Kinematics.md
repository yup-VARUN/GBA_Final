# Game Kinematics
Entire set of kinematics could be thought of as a state vector which defines the state of a sprite at any given time step t.

### State Vector
This game will have two main sprintes, a set of mechazilla arms(just like the ones SpaceX have for catching the starship's booster). Each sprite will have a 
Dynamics equations for each parameter(each parameter HAVE to be updated, write logic for each!)

$
State Vector = [
                X, Y, V_x, V_y, A_x, A_y,
            ]\\
$

There're HAVE to be some game constraints which will allow it to make some sense:
    - Thrust profile has to be already fed

Define Winning Condition	(Loosing will then become !Winning)
Define Levels	


# Developlmental Milestones:
Vertical Landing with a perfect 

# Unit Tests:
- Test the kinematics equations with random thrust vector curve and plot graphs to see if the state vector makes sense.
    - Do it with only `x` and `y` coordinates with `V_x`, `V_y` first.
