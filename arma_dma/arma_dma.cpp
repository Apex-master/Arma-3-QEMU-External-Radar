#include <stdio.h>
#include <unistd.h>
#include <thread>
#include "game.hpp"

Memory arma_mem;

bool active = true;
bool main_t = false;
bool write_t = false;
uint64_t g_base;

void read_th()
{
	main_t = true;
	while (main_t)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		while (g_base != 0)
		{
			std::vector<player_t> tmp{};

			for (uint32_t ai_center = 0; ai_center < 4; ai_center++)
			{
				uint64_t allunits_ptr;
				arma_mem.Read<uint64_t>(SDK::GetWorld() + 0x2948 + (ai_center * 0x8), allunits_ptr);

				if (allunits_ptr)
				{
					uint64_t groups_table_ptr;
					arma_mem.Read<uint64_t>(allunits_ptr + 0x48, groups_table_ptr);

					uint32_t groups_table_ptr_size;
					arma_mem.Read<uint32_t>((allunits_ptr + 0x48) + 0x8, groups_table_ptr_size);

					if (groups_table_ptr && groups_table_ptr_size)
					{
						for (uint32_t groups_table = 0; groups_table < groups_table_ptr_size; groups_table++)
						{
							uint64_t units_ptr;
							arma_mem.Read<uint64_t>(groups_table_ptr + (groups_table * 0x8), units_ptr);

							uint64_t unit_players_ptr;
							arma_mem.Read<uint64_t>(units_ptr + 0x160, unit_players_ptr);

							uint32_t unit_players_ptr_size;
							arma_mem.Read<uint32_t>((units_ptr + 0x160) + 0x8, unit_players_ptr_size);

							if (unit_players_ptr && unit_players_ptr_size)
							{
								for (uint32_t player_l = 0; player_l < unit_players_ptr_size; player_l++)
								{
									uint64_t player_link;
									arma_mem.Read<uint64_t>(unit_players_ptr + (player_l * 0x38), player_link);

									uint64_t player_path_v1;
									arma_mem.Read<uint64_t>(player_link + 0x8, player_path_v1);

									uint64_t player_path_v2;
									arma_mem.Read<uint64_t>(player_path_v1 + 0xC8, player_path_v2);

									uint64_t player_ptr;
									arma_mem.Read<uint64_t>(player_path_v2 + 0x8, player_ptr);

									if (player_ptr)
									{
										player_t player{};
										player.player_ptr = player_ptr;
										tmp.push_back(player); // send data to temp array
									}
								}
							}
						}
					}
				}
			}
			Data::players = tmp; // send temp array to player array
			Data::EmitData();	 // convert player array into json and emit the json to nodejs using socket.io
		}
	}
	main_t = false;
}

void write_th()
{
	write_t = true;

	while (write_t)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		while (g_base != 0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			SDK::AimAssist();
		}
	}
	write_t = false;
}

int main(int argc, char *argv[])
{

	if (geteuid() != 0)
	{
		printf("Error: %s is not running as root\n", argv[0]);
		return 0;
	}

	Data::ConnectSocket();
	const char *ap_proc = "Arma3_x64.exe";
	std::thread read_thr;
	std::thread write_thr;

	while (active)
	{
		if (arma_mem.get_proc_status() != process_status::FOUND_READY)
		{
			if (main_t)
			{
				main_t = false;
				write_t = false;
				g_base = 0;
				read_thr.~thread();
				write_thr.~thread();
			}

			std::this_thread::sleep_for(std::chrono::seconds(1));
			printf("Searching for arma process...\n");

			arma_mem.open_proc(ap_proc);

			if (arma_mem.get_proc_status() == process_status::FOUND_READY)
			{
				g_base = arma_mem.get_proc_baseaddr();
				printf("\nArma process found\n");
				printf("Base: %lx\n", g_base);

				read_thr = std::thread(read_th);
				read_thr.detach();

				write_thr = std::thread(write_th);
				write_thr.detach();
			}
		}
		else
		{
			arma_mem.check_proc();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	return 0;
}