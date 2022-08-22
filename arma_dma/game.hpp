#include <iostream>
#include <sio_client.h>
#include "globals.hpp"
#include "utils/json.hpp"
#include "memory.h"

using namespace sio;

extern Memory arma_mem;
extern uint64_t g_base;

class Vector3
{

public:
	Vector3() : x(0.f), y(0.f), z(0.f){}
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z){}
	~Vector3(){}
	float x, y, z;
};

namespace SDK
{

	uint64_t GetWorld()
	{
		uint64_t get_world;
		arma_mem.Read<uint64_t>(g_base + 0x26166D8, get_world);
		return get_world;
	}

	uint64_t GetLocalPlayer()
	{
		uint64_t local_player;
		arma_mem.Read<uint64_t>(GetWorld() + 0x2A60, local_player);

		uint64_t local_player_l;
		arma_mem.Read<uint64_t>(local_player + 0x8, local_player_l);
		return local_player_l;
	}

	uint64_t GetCameraOn()
	{
		uint64_t camera_on;
		arma_mem.Read<uint64_t>(SDK::GetWorld() + 0x2A30, camera_on);
		return camera_on;
	}

	uint64_t GetCamera()
	{
		uint64_t camera;
		arma_mem.Read<uint64_t>(GetWorld() + 0xA08, camera);
		return camera;
	}

	uint64_t GetAIUnitInfo(uint64_t player)
	{
		uint64_t player_info;
		arma_mem.Read<uint64_t>(player + 0xA98, player_info);
		return player_info;
	}

	uint64_t GetPlayerSide(uint64_t player)
	{
		uint8_t player_side;
		arma_mem.Read<uint8_t>(player + 0x340, player_side);
		return player_side;
	}

	uint64_t GetPlayerDead(uint64_t player)
	{
		uint8_t player_dead;
		arma_mem.Read<uint8_t>(player + 0x504, player_dead);
		return player_dead;
	}

	uint64_t IsPlayerInVehicle(uint64_t player)
	{
		uint64_t player_vehicle;
		arma_mem.Read<uint64_t>(player + 0x368, player_vehicle);

		uint64_t player_vehicle_check;
		arma_mem.Read<uint64_t>(player_vehicle + 0x8, player_vehicle_check);

		if (player_vehicle_check) {
			return 1;
		} else {
			return 0;
		}
	}

	uint64_t GetPlayerDirection(uint64_t player)
	{
		uint64_t player_info;
		arma_mem.Read<uint64_t>(player + 0xD0, player_info);

		float player_direction_x;
		arma_mem.Read<float>(player_info + 0x20, player_direction_x);

		float player_direction_y;
		arma_mem.Read<float>(player_info + 0x20 + 8, player_direction_y);

		float radians = atan2(player_direction_y, player_direction_x);
		float degrees = (radians * 180 / 3.14159265358979323846);
		degrees = 90 - degrees;

		if (degrees < 0)
		{
			degrees += 360;
		}

		return degrees;
	}

	Vector3 GetPlayerPosition(uintptr_t player)
	{
		if (player == GetLocalPlayer())
		{
			uintptr_t player_info;
			arma_mem.Read<uintptr_t>(player + 0xD0, player_info);

			Vector3 player_position;
			arma_mem.Read<Vector3>(player_info + 0x2C, player_position);

			return player_position;
		}
		else
		{
			uintptr_t player_info;
			arma_mem.Read<uintptr_t>(player + 0x190, player_info);

			Vector3 player_position;
			arma_mem.Read<Vector3>(player_info + 0x2C, player_position);

			return player_position;
		}
	}

	void AimAssist()
	{
		arma_mem.Write<float>(g_base + 0x2662B04, 0.f);  // no recoil (not setUnitRecoilCoefficient)
		arma_mem.Write<float>(g_base + 0x2662A30, 0.f);  // no sway v1 (not setCustomAimCoef)
		arma_mem.Write<float>(g_base + 0x2662A60, 0.f);  // no sway v2 (not setCustomAimCoef)
	}

}

namespace Data
{

	std::vector<player_t> players = {};
	sio::client io;

	void ConnectSocket()
	{
	    	io.connect("http://127.0.0.1:7000");
		io.socket()->emit("server");
    		printf("connected");
	}

	void EmitData()
	{
		nlohmann::json j;

		for (uint32_t i = 0; i < players.size(); i++)
		{
			auto player = players[i];

			Vector3 playerPosition = SDK::GetPlayerPosition(player.player_ptr);
    			int player_side = (int)SDK::GetPlayerSide(player.player_ptr);
      			int player_dead = (int)SDK::GetPlayerDead(player.player_ptr);
      			int playerDirection = (int)SDK::GetPlayerDirection(player.player_ptr);
      			bool playerInVehicle = (bool)SDK::IsPlayerInVehicle(player.player_ptr);
			const auto _i = std::to_string(i);

			j["coords"][_i]["player_y"] = playerPosition.x;
			// printf("\n\n Player X: %i\n", (int)PlayerPosition.x);
			j["coords"][_i]["player_x"] = playerPosition.z;
			// printf("Player Y: %i\n", (int)PlayerPosition.z);
			j["coords"][_i]["player_side"] = player_side;
			// printf("Player Side: %i\n", player_side);
			j["coords"][_i]["player_dead"] = player_dead;
			// printf("Player Dead: %i\n", player_dead);
			j["coords"][_i]["player_direction"] = playerDirection;
			// printf("Player Direction: %i\n", playerDirection);
			j["coords"][_i]["player_in_vehicle"] = playerInVehicle;
			// printf("Player In Vehicle: %b\n", playerInVehicle);
		}

		const auto s = j.dump();
		io.socket()->emit("json", s);

    		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
