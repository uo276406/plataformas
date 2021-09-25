#include "Player.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/jugador.png", x, y, 35, 37, game) {

	orientation = Orientation::RIGHT;
	state = States::MOVING;

	aShootingRight = new Animation("res/jugador_disparando_derecha.png",
		width, height, 160, 40, 6, 4, false, game);
	aShootingLeft = new Animation("res/jugador_disparando_izquierda.png",
		width, height, 160, 40, 6, 4, false, game);
	aIdleRight = new Animation("res/jugador_idle_derecha.png", width, height,
		320, 40, 6, 8, true,game);
	aIdleLeft = new Animation("res/jugador_idle_izquierda.png", width, height,
		320, 40, 6, 8, true, game);
	aRunningRight = new Animation("res/jugador_corriendo_derecha.png", width, height,
		320, 40, 6, 8, true, game);
	aRunningLeft = new Animation("res/jugador_corriendo_izquierda.png", width, height,
		320, 40, 6, 8, true, game);

	animation = aIdleRight;


}

Projectile* Player::shoot() {
	if (shootTime == 0) {
		state = States::SHOOTING;
		shootTime = shootCadence;

		aShootingLeft->currentFrame = 0; //"Rebobinar" animación
		aShootingRight->currentFrame = 0; //"Rebobinar" animación
		Projectile* projectile = new Projectile(x, y, game);
		if (orientation == Orientation::LEFT) {
			projectile->vx *= -1; // Invertir
		}
		return projectile;

	}
	else {
		return NULL;
	}
}


void Player::update() {

	bool endAnimation = animation->update();

	// Acabo la animación, no sabemos cual
	if (endAnimation) {
		// Estaba disparando
		if (state == States::SHOOTING) {
			state = States::MOVING;
		}
	}


	// Establecer orientación
	if (vx > 0) {
		orientation = Orientation::RIGHT;
	}
	if (vx < 0) {
		orientation = Orientation::LEFT;
	}


	// Selección de animación basada en estados
	if (state == States::SHOOTING) {

		animation = orientation == Orientation::RIGHT ?
			aShootingRight : aShootingLeft;
		
	}
	if (state == States::MOVING) {
		if (vx != 0) {

			animation = orientation == Orientation::RIGHT ?
				aRunningRight : aRunningLeft;
			
		}
		if (vx == 0) {
			animation = orientation == Orientation::RIGHT ?
				aIdleRight : aIdleLeft;

		}
	}




	if (shootTime > 0) {
		shootTime--;
	}

	x = x + vx;
	y = y + vy;
}

void Player::moveX(float axis) {
	vx = axis * 3;
}

void Player::moveY(float axis) {
	vy = axis * 3;
}

void Player::draw() {
	animation->draw(x, y);
}


