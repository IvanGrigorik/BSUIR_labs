.model small
.stack 100h

.data
enemies_count               equ 3
screen_size                 equ 80 * 25
screen_width                equ 80
screen_heigth               equ 25
green_screen                equ 2020h
red_screen                  equ 4020h
bullet                      equ 0E04h
wall                        equ 6620h
ground                      equ 0620h
empty                       equ 0720h
enemy_go_up                 equ 041Eh
enemy_go_down               equ 041Fh
enemy_go_left               equ 0411h
enemy_go_right              equ 0410h
player_go_up                equ 021Eh
player_go_down              equ 021Fh
player_go_left              equ 0211h
player_go_right             equ 0210h
enemy_base                  equ 04B1h
status_dead                 equ 0
status_dead_has_bullet      equ 1
status_can_shoot            equ 2
status_can_not_shoot        equ 3
direction_up                equ 0
direction_down              equ 1
direction_left              equ 2
direction_right             equ 3
direction_none              equ 4
shoot_bullet                equ 5
exit                        equ 6
min_x                       equ 0
max_x                       equ 79
min_y                       equ 1
max_y                       equ 24
bullet_destroyed            equ 0
bullet_fine                 equ 1
bullet_out_of_bound         equ 2
cx_delay                    equ 2
dx_delay                    equ 4585h
long_cx_delay               equ 50
victory_word_size           equ 7
fail_word_size              equ 9

gbbl                        equ 00100000b
rbbl                        equ 01000000b

screen                      dw screen_size dup (?)
enemies_positions           dw enemies_count dup (?)
enemies_status              db enemies_count dup (?)
enemies_directions          db enemies_count dup (?)
enemies_bullets_position    dw enemies_count dup (?)
enemies_bullets_direction   db enemies_count dup (?)
player_position             dw ?
player_direction            db ?
player_status               db ?
player_bullet_position      dw ?
player_bullet_direction     db ?
desired_action              db ?
player_killed               db ?
destroyed_base              db ?

victory_word                db 'Y', gbbl, 'o', gbbl, 'u', gbbl, ' ', gbbl, 'w', gbbl, 'i', gbbl, 'n', gbbl
fail_word                   db 'G', rbbl, 'a', rbbl, 'm', rbbl, 'e', rbbl, ' ', rbbl, 'o', rbbl, 'v', rbbl, 'e', rbbl, 'r', rbbl

.code
jmp         start

delay macro
    push        dx
    push        cx
    mov         cx, cx_delay
    mov         dx, dx_delay
    mov         ah, 86h
    int         15h
    pop         cx
    pop         dx
endm

long_delay macro
    push        dx
    push        cx
    mov         cx, long_cx_delay
    ; Create delay
    mov         dx, dx_delay
    mov         ah, 86h
    int         15h
    pop         cx
    pop         dx
endm

set_video_mode proc
    push        ax

    mov         ah, 0
    mov         al, 03h
    int         10h

    set_video_mode_end:
    pop         ax
    ret
endp

update_screen proce
    push        ax
    push        es
    push        si
    push        di
    push        cx

    mov         ax, 0B800h
    mov         es, ax
    mov         di, 0
    mov         cx, screen_size
    mov         si, offset screen
    rep         movsw

    update_screen_end:
    pop         cx
    pop         di
    pop         si
    pop         es
    pop         ax
    ret
endp

load_map proc
    push        ax
    push        di
    push        cx
    push        es

    mov         ax, ds
    mov         es, ax
    mov         di, offset screen
    mov         cx, screen_width
    mov         ax, empty
    rep         stosw
    mov         cx, screen_width
    mov         ax, wall
    rep         stosw

    mov         cx, 11
    load_map_loop:
        push        cx
        mov         ax, wall
        stosw

        mov         cx, (screen_width - 2) / 5
        load_map_loop1:
            push        cx
            mov         ax, ground
            mov         cx, 2
            rep         stosw
            mov         ax, wall
            mov         cx, 3
            rep         stosw
            pop         cx
        loop load_map_loop1
        mov         ax, wall
        stosw

        mov         ax, wall
        stosw

        mov         cx, screen_width - 2
        mov         ax, ground
        rep         stosw

        mov         ax, wall
        stosw

        pop         cx
    loop load_map_loop
    mov         cx, screen_width
    mov         ax, wall
    rep         stosw

    mov         di, offset screen
    mov         ah, screen_heigth / 2
    mov         al, (screen_width / 2) + 1
    call        get_offset_on_screen
    add         di, ax
    mov         [di], enemy_base

    load_map_end:
    pop         es
    pop         cx
    pop         di
    pop         ax
    ret
endp

save_enemy_pos proc; al - x, ah - y, cx - enemy_index
    push        cx
    push        di

    add         cx, cx
    mov         di, offset enemies_positions
    add         di, cx
    mov         [di], ax

    save_enemy_pos_end:
    pop         di
    pop         cx
    ret
endp

get_enemy_pos proc; cx - enemy_index; output: al - x, ah - y
    push        cx
    push        di

    add         cx, cx
    mov         di, offset enemies_positions
    add         di, cx
    mov         ax, [di]

    get_enemy_pos_end:
    pop         di
    pop         cx
    ret
endp

store_enemy_direction proc; cx - enemy_index, al - enemy_direction
    push        di

    mov         di, offset enemies_directions
    add         di, cx
    mov         [di], al

    store_enemy_direction_end:
    pop         di
    ret
endp

get_enemy_direction proc; cx - enemy_index; output: al - enemy_direction
    push        di

    mov         di, offset enemies_directions
    add         di, cx
    mov         al, [di]

    get_enemy_direction_end:
    pop         di
    ret
endp

store_enemy_status proc; cx - enemy_index, al - enemy status
    push        di

    mov         di, offset enemies_status
    ; For which enemy
    add         di, cx
    mov         [di], al

    pop         di
    ret
endp

get_enemy_status proc; cx - enemy_index; output: al - enemy status
    push        di

    mov         di, offset enemies_status
    add         di, cx
    mov         al, [di]

    get_enemy_status_end:
    pop         di
    ret
endp

get_offset_on_screen proc; al - x, ah - y; output: ax - offset_on_screen
    push        cx
    push        bx
    push        dx

    mov         cx, ax; cx - stores pos
    mov         al, ah; al - y
    xor ah, ah; ax - y
    mov         bx, screen_width
    mul bx
    xor ch, ch; cx - x
    add         ax, cx; ax - index on screen
    add         ax, ax; ax - offset on screen

    get_offset_on_screen_end:
    pop         dx
    pop         bx
    pop         cx
    ret
endp

draw_enemy proc; cx - enemy_index
    push        di
    push        ax
    push        dx

    call        get_enemy_status
    cmp         al, status_dead
    jz          draw_enemy_end
    cmp         al, status_dead_has_bullet
    jz          draw_enemy_end

    call        get_enemy_tank_sprite
    mov         dx, ax; dx - sprite to draw

    call        get_enemy_pos
    call        get_offset_on_screen
    mov         di, offset screen
    add         di, ax; di - enemy offset on screen
    mov         [di], dx

    draw_enemy_end:
    pop         dx
    pop         ax
    pop         di
    ret
endp

get_enemy_tank_sprite proc; cx - enemy_index; output: ax - enemy_tank_sprite

    call        get_enemy_direction
    cmp         al, direction_up
    jz          get_tank_sprite_up
    cmp         al, direction_down
    jz          get_tank_sprite_down
    cmp         al, direction_left
    jz          get_tank_sprite_left
    jmp         get_tank_sprite_right

    get_tank_sprite_up:
    mov         ax, enemy_go_up
    jmp         get_tank_sprite_end
    get_tank_sprite_down:
    mov         ax, enemy_go_down
    jmp         get_tank_sprite_end
    get_tank_sprite_left:
    mov         ax, enemy_go_left
    jmp         get_tank_sprite_end
    get_tank_sprite_right:
    mov         ax, enemy_go_right
    jmp         get_tank_sprite_end

    get_tank_sprite_end:
    ret
endp

get_enemy_bullet_pos proc; cx - enemy_index; output: al - x, ah - y
    push        di

    mov         di, offset enemies_bullets_position
    add         di, cx
    add         di, cx
    mov         ax, [di]

    get_enemy_bullet_pos_end:
    pop         di
    ret
endp

set_enemy_bullet_pos proc; cx - enemy_index, al - x, ah - y
    push        di

    mov         di, offset enemies_bullets_position
    add         di, cx
    add         di, cx
    mov         [di], ax

    set_enemy_bullet_pos_end:
    pop         di
    ret
endp

get_enemy_bullet_direction proc; cx - enemy_index; output: bl - direction
    push        di

    mov         di, offset enemies_bullets_direction
    add         di, cx
    mov         bl, [di]

    get_enemy_bullet_direction_end:
    pop         di
    ret
endp

set_enemy_bullet_direction proc; cx - enemy_index, bl - direction
    push        di

    mov         di, offset enemies_bullets_direction
    add         di, cx
    mov         [di], bl

    set_enemy_bullet_direction_end:
    pop         di
    ret
endp

get_player_pos proc; output: al - x, ah - y
    mov         ax, player_position
    get_player_pos_end:
    ret
endp

store_player_pos proc; al - x, ah - y
    mov         player_position, ax
    store_player_pos_end:
    ret
endp

get_player_direction proc; output: al - player direction

    mov         al, player_direction

    get_player_direction_end:
    ret
endp

store_player_direction proc; al - player direction

    mov         player_direction, al

    store_player_direction_end:
    ret
endp

get_player_status proc; output: al - player status

    mov         al, player_status

    get_player_status_end:
    ret
endp

save_player_status proc; al - player status

    mov         player_status, al

    save_player_status_end:
    ret
endp

draw_player proc; no input, no output
    push        ax
    push        dx
    push        di

    cmp         player_killed, 1
    jz          draw_player_end

    call        get_player_tank_sprite
    mov         dx, ax; dx - sprite to draw

    call        get_player_pos
    call        get_offset_on_screen
    mov         di, offset screen
    add         di, ax
    mov         [di], dx

    draw_player_end:
    pop         di
    pop         dx
    pop         ax
    ret
endp

get_player_tank_sprite proc; output: ax - player_tank_sprite

    call        get_player_direction

    cmp         al, direction_up
    jz          get_player_direction_up
    cmp         al, direction_down
    jz          get_player_direction_down
    cmp         al, direction_left
    jz          get_player_direction_left
    jmp         get_player_direction_right

    get_player_direction_up:
    mov         ax, player_go_up
    jmp         get_player_direction_end
    get_player_direction_down:
    mov         ax, player_go_down
    jmp         get_player_direction_end
    get_player_direction_left:
    mov         ax, player_go_left
    jmp         get_player_direction_end
    get_player_direction_right:
    mov         ax, player_go_right
    jmp         get_player_direction_end

    get_player_tank_sprite_end:
    ret
endp

get_player_bullet_pos proc; output: al - x, ah - y

    mov         ax, player_bullet_position

    get_player_bullet_pos_end:
    ret
endp

get_player_bullet_direction proc; output: bl - direction

    mov         bl, player_bullet_direction

    get_player_bullet_direction_end:
    ret
endp

set_player_bullet_pos proc; al - x, ah - y

    mov         player_bullet_position, ax

    set_player_bullet_pos_end:
    ret
endp

set_player_bullet_direction proc; al - direction

    mov         player_bullet_direction, al

    set_player_bullet_direction_end:
    ret
endp

init proc
    push        ax
    push        cx

    call        load_map

    mov         player_killed, 0
    mov         destroyed_base, 0

    ; initialize enemies positions
    mov         al, min_x + 1
    mov         ah, min_y + 1
    mov         cx, 0
    call        save_enemy_pos
    mov         al, screen_width / 2
    mov         ah, min_y + 1
    inc cx
    call        save_enemy_pos
    mov         al, min_x + 1
    mov         ah, screen_heigth / 2
    inc cx
    call        save_enemy_pos

    mov         cx, 0; init enemies status
    mov         al, status_can_shoot
    call        store_enemy_status
    inc cx
    call        store_enemy_status
    inc cx
    call        store_enemy_status

    mov         cx, 0; init enemies directions
    mov         al, direction_up
    call        store_enemy_direction
    inc cx
    call        store_enemy_direction
    inc cx
    call        store_enemy_direction

    mov         cx, 0; draw enemies
    call        draw_enemy
    inc cx
    call        draw_enemy
    inc cx
    call        draw_enemy

    mov         al, max_x - 20 ;init player
    mov         ah, max_y - 13
    call        store_player_pos

    mov         al, direction_up
    call        store_player_direction

    mov         al, status_can_shoot
    call        save_player_status

    call        draw_player  ; draw player

    init_end:
    pop         cx
    pop         ax
    ret
endp

choose_desired_action proc  ; al - ASCII, ah - scan_code; output: desired_action changed if legal
    cmp         ah, 01h     ; Esc key
    jz          choose_desired_action_exit
    cmp         ah, 11h     ; W key
    jz          choose_desired_action_up
    cmp         ah, 1Eh     ; A key
    jz          choose_desired_action_left
    cmp         ah, 1Fh     ; S key
    jz          choose_desired_action_down
    cmp         ah, 20h     ; D key
    jz          choose_desired_action_right
    cmp         ah, 39h     ; SpaceBar
    jz          choose_desired_action_shoot
    jmp         choose_desired_action_end

    choose_desired_action_exit:
    mov         desired_action, exit
    jmp         choose_desired_action_end
    choose_desired_action_up:
    mov         desired_action, direction_up
    jmp         choose_desired_action_end
    choose_desired_action_down:
    mov         desired_action, direction_down
    jmp         choose_desired_action_end
    choose_desired_action_left:
    mov         desired_action, direction_left
    jmp         choose_desired_action_end
    choose_desired_action_right:
    mov         desired_action, direction_right
    jmp         choose_desired_action_end
    choose_desired_action_shoot:
    mov         desired_action, shoot_bullet
    jmp         choose_desired_action_end

    choose_desired_action_end:
    ret
endp

get_desired_action proc; output: desired_action
    push        ax

    mov         desired_action, direction_none
    get_desired_action_loop:
        ; Check to have symbol in buffer
        mov         ah, 11h
        int         16h
        jz          get_desired_action_end
        ; Get action
        mov         ah, 10h
        int         16h
        call        choose_desired_action
    jmp         get_desired_action_loop

    get_desired_action_end:
    pop         ax
    ret
endp

erase proc; al - x, ah - y
    push        di
    push        ax

    call        get_offset_on_screen
    mov         di, offset screen
    add         di, ax
    mov         [di], ground

    erase_end:
    pop         ax
    pop         di
    ret
endp

check_boundaries proc; al - x, ah - y; output: al - checked x, ah - checked y

    cmp         ah, min_y
    jb check_boundaries_ah_too_small
    cmp         ah, max_y
    ja          check_boundaries_ah_too_big
    jmp         check_boundaries_ah_fine

    check_boundaries_ah_too_big:
    mov         ah, max_y
    jmp         check_boundaries_ah_fine
    check_boundaries_ah_too_small:
    mov         ah, min_y
    jmp         check_boundaries_ah_fine

    check_boundaries_ah_fine:

    cmp         al, min_x
    jb check_boundaries_al_too_small
    cmp         al, max_x
    ja          check_boundaries_al_too_big
    jmp         check_boundaries_end

    check_boundaries_al_too_small:
    mov         al, min_x
    jmp         check_boundaries_end
    check_boundaries_al_too_big:
    mov         al, max_x
    jmp         check_boundaries_end

    check_boundaries_end:
    ret
endp

get_new_pos proc; al - x, ah - y, bl - direction; al - new x, ah - new y (checked)

    cmp         bl, direction_right
    jz          get_new_pos_right
    cmp         bl, direction_left
    jz          get_new_pos_left
    cmp         bl, direction_up
    jz          get_new_pos_up
    cmp         bl, direction_down
    jz          get_new_pos_down
    jmp         get_new_pos_end

    get_new_pos_up:
    cmp         ah, 0
    jz          get_new_pos_end
    dec ah
    jmp         get_new_pos_end
    get_new_pos_down:
    inc ah
    jmp         get_new_pos_end
    get_new_pos_left:
    cmp         al, 0
    jz          get_new_pos_end
    dec al
    jmp         get_new_pos_end
    get_new_pos_right:
    inc al
    jmp         get_new_pos_end

    get_new_pos_end:
    call        check_boundaries
    ret
endp

get_element_on_screen proc; al - x, ah - y; output: dx - element
    push        ax
    push        di

    call        get_offset_on_screen
    mov         di, offset screen
    add         di, ax
    mov         dx, [di]

    get_element_on_screen_end:
    pop         di
    pop         ax
    ret
endp

draw_bullet proc; al - x, ah - y
    push        ax
    push        di

    call        get_offset_on_screen
    mov         di, offset screen
    add         di, ax
    mov         word ptr [di], bullet

    draw_bullet_end:
    pop         di
    pop         ax
    ret
endp

deside_if_bullet_destroyed proc; al - new x, ah - new y; output: bl - bullet_state
    push        dx

    call        get_element_on_screen
    cmp         dx, bullet
    jz          deside_if_bullet_destroyed_out_of_bound
    cmp         dx, ground
    jz          deside_if_bullet_destroyed_fine
    jmp         deside_if_bullet_destroyed_destroyed

    deside_if_bullet_destroyed_out_of_bound:
    mov         bl, bullet_out_of_bound
    jmp         deside_if_bullet_destroyed_end
    deside_if_bullet_destroyed_fine:
    mov         bl, bullet_fine
    jmp         deside_if_bullet_destroyed_end
    deside_if_bullet_destroyed_destroyed:
    mov         bl, bullet_destroyed
    cmp         dx, enemy_base
    jz          deside_if_bullet_destroyed_destroyed_base
    cmp         dx, player_go_down
    jz          deside_if_bullet_destroyed_player_killed
    cmp         dx, player_go_up
    jz          deside_if_bullet_destroyed_player_killed
    cmp         dx, player_go_left
    jz          deside_if_bullet_destroyed_player_killed
    cmp         dx, player_go_right
    jz          deside_if_bullet_destroyed_player_killed
    jmp         deside_if_bullet_destroyed_end

    deside_if_bullet_destroyed_destroyed_base:
    mov         destroyed_base, 1
    jmp         deside_if_bullet_destroyed_end

    deside_if_bullet_destroyed_player_killed:
    mov         player_killed, 1
    jmp         deside_if_bullet_destroyed_end

    deside_if_bullet_destroyed_end:
    pop         dx
    ret
endp

draw_bullet_result proc; al - x, ah - y, bl - bullet_state

    cmp         bl, bullet_out_of_bound
    jz          draw_bullet_result_end
    cmp         bl, bullet_fine
    jne draw_bullet_result_empty
    call        draw_bullet
    jmp         draw_bullet_result_end

    draw_bullet_result_empty:
    call        erase
    jmp         draw_bullet_result_end

    draw_bullet_result_end:
    ret
endp

update_bullet proc; al - x, ah - y, bl - direction; output: al - new x, ah - new y, bl - bullet state
    push        dx

    push        ax
    mov         dx, ax
    call        get_new_pos
    cmp         dx, ax
    jne update_bullet_no_out_of_bound
    call        draw_bullet
    update_bullet_no_out_of_bound:
    call        deside_if_bullet_destroyed
    call        draw_bullet_result

    mov         dx, ax
    pop         ax
    call        erase
    mov         ax, dx

    update_bullet_end:
    pop         dx
    ret
endp

set_enemy_bullet_status_active proc; cx - enemy_index
    push        ax

    call        get_enemy_status
    cmp         al, status_dead
    jz          set_enemy_bullet_status_active_dead
    cmp         al, status_dead_has_bullet
    jz          set_enemy_bullet_status_active_dead
    jmp         set_enemy_bullet_status_active_alive

    set_enemy_bullet_status_active_dead:
    mov         al, status_dead_has_bullet
    call        store_enemy_status
    jmp         set_enemy_bullet_status_active_end

    set_enemy_bullet_status_active_alive:
    mov         al, status_can_not_shoot
    call        store_enemy_status
    jmp         set_enemy_bullet_status_active_end

    set_enemy_bullet_status_active_end:
    pop         ax
    ret
endp

set_enemy_bullet_status_inactive proc; cx - enemy_index
    push        ax

    call        get_enemy_status
    cmp         al, status_dead
    jz          set_enemy_bullet_status_inactive_dead
    cmp         al, status_dead_has_bullet
    jz          set_enemy_bullet_status_inactive_dead
    jmp         set_enemy_bullet_status_inactive_alive

    set_enemy_bullet_status_inactive_dead:
    mov         al, status_dead
    call        store_enemy_status
    jmp         set_enemy_bullet_status_inactive_end

    set_enemy_bullet_status_inactive_alive:
    mov         al, status_can_shoot
    call        store_enemy_status
    jmp         set_enemy_bullet_status_inactive_end

    set_enemy_bullet_status_inactive_end:
    pop         ax
    ret
endp

save_enemy_bullet_state proc; cx - enemy_index, bl - bullet_state

    cmp         bl, bullet_fine
    jz          save_enemy_bullet_state_fine
    call        set_enemy_bullet_status_inactive
    jmp         save_enemy_bullet_state_end

    save_enemy_bullet_state_fine:
    call        set_enemy_bullet_status_active
    jmp         save_enemy_bullet_state_end

    save_enemy_bullet_state_end:
    ret
endp

update_enemy_bullet proc; cx - number of enemy
    push        cx
    push        ax
    push        bx

    dec cx; turn cx to index
    call        get_enemy_status

    cmp         al, status_dead
    jz          update_enemy_bullet_end
    cmp         al, status_can_shoot
    jz          update_enemy_bullet_end

    call        get_enemy_bullet_pos
    call        get_enemy_bullet_direction
    call        update_bullet
    call        save_enemy_bullet_state
    call        set_enemy_bullet_pos

    update_enemy_bullet_end:
    pop         bx
    pop         ax
    pop         cx
    ret
endp

save_player_bullet_status_active proc;
    push        ax

    call        get_player_status
    cmp         al, status_dead
    jz          save_player_bullet_status_active_dead
    cmp         al, status_dead_has_bullet
    jz          save_player_bullet_status_active_dead

    mov         al, status_can_not_shoot
    call        save_player_status
    jmp         save_player_bullet_status_active_end

    save_player_bullet_status_active_dead:
    mov         al, status_dead_has_bullet
    call        save_player_status

    save_player_bullet_status_active_end:
    pop         ax
    ret
endp

save_player_bullet_status_inactive proc;
    push        ax

    call        get_player_status
    cmp         al, status_dead
    jz          save_player_bullet_status_inactive_dead
    cmp         al, status_dead_has_bullet
    jz          save_player_bullet_status_inactive_dead

    mov         al, status_can_shoot
    call        save_player_status
    jmp         save_player_bullet_status_inactive_end

    save_player_bullet_status_inactive_dead:
    mov         al, status_dead
    call        save_player_status

    save_player_bullet_status_inactive_end:
    pop         ax
    ret
endp

save_player_bullet_state proc; bl - bullet_state

    cmp         bl, bullet_fine
    jz          save_player_bullet_state_active
    call        save_player_bullet_status_inactive
    jmp         save_player_bullet_state_end

    save_player_bullet_state_active:
    call        save_player_bullet_status_active
    jmp         save_player_bullet_state_end

    save_player_bullet_state_end:
    ret
endp

update_player_bullet proc;
    push        ax

    call        get_player_status

    cmp         al, status_can_shoot
    jz          update_player_bullet_end
    cmp         al, status_dead
    jz          update_player_bullet_end

    call        get_player_bullet_pos
    call        get_player_bullet_direction
    call        update_bullet
    call        save_player_bullet_state
    call        set_player_bullet_pos

    update_player_bullet_end:
    pop         ax
    ret
endp

update_bullets proc
    push        cx

    mov         cx, enemies_count
    update_bullets_enemies_loop:
        call        update_enemy_bullet
    loop update_bullets_enemies_loop

    call        update_player_bullet

    update_bullets_end:
    pop         cx
    ret
endp

player_shoot proc
    push        ax

    call        get_player_status
    cmp         al, status_can_not_shoot
    jz          player_shoot_end

    call        get_player_pos
    call        set_player_bullet_pos
    call        get_player_direction
    call        set_player_bullet_direction
    mov         al, status_can_not_shoot
    call        save_player_status
    call        update_player_bullet

    player_shoot_end:
    pop         ax
    ret
endp

player_move proc

    call        get_player_pos
    call        erase
    mov         bl, desired_action
    push        ax
    mov         al, desired_action
    call        store_player_direction
    pop         ax
    call        get_new_pos
    call        get_element_on_screen
    cmp         dx, ground
    jz          player_move_can_move
    cmp         dx, bullet
    jz          player_move_bullet
    jmp         player_move_end

    player_move_bullet:
    mov         player_killed, 1
    jmp         player_move_end

    player_move_can_move       :
    call        store_player_pos
    jmp         player_move_end

    player_move_end:
    ret
endp

update_player proc

    cmp         player_killed, 1
    jz          update_player_end

    cmp         desired_action, direction_none
    jz          update_player_finished_action

    cmp         desired_action, shoot_bullet
    jz          update_player_shoot

    jmp         update_player_move
    update_player_shoot:
    call        player_shoot
    jmp         update_player_finished_action

    update_player_move:
    call        player_move
    jmp         update_player_finished_action


    update_player_finished_action:

    call        draw_player

    update_player_end:
    ret
endp

get_difference proc; ch - a, cl - b; output: ch - difference

    cmp         ch, cl
    ja          get_difference_ah_greater
    sub         cl, ch
    mov         ch, cl

    get_difference_ah_greater:
    sub         ch, cl
    jmp         get_differenc_end

    get_differenc_end:
    ret
endp

get_distance_to_player proc; cx - enemy_index; output: ah - y difference, al - x difference
    push        cx
    push        bx

    call        get_player_pos
    mov         bx, ax
    call        get_enemy_pos

    mov         ch, bl
    mov         cl, al
    call        get_difference
    mov         al, ch

    mov         ch, bh
    mov         cl, ah
    call        get_difference
    mov         ah, ch

    get_distance_to_player_end:
    pop         bx
    pop         cx
    ret
endp

update_enemy_vertical_action proc; cx - enemy_index, al - final_flag
    push        ax
    push        bx
    push        ax

    call        get_player_pos
    mov         bx, ax
    call        get_enemy_pos

    cmp         ah, bh; bh - player, ah - enemy
    jz          update_enemy_vertical_action_to_shoot
    ja          update_enemy_vertical_action_up
    jmp         update_enemy_vertical_action_down

    update_enemy_vertical_action_up:
    call        update_enemy_move_up
    cmp         bl, 1
    jz          update_enemy_vertical_action_end_pop
            pop         ax
    cmp         al, 1
    jz          update_enemy_vertical_action_end
    mov         al, 1
    call        update_enemy_horizontal_action
    jmp         update_enemy_vertical_action_end

    update_enemy_vertical_action_down:
    call        update_enemy_move_down
    cmp         bl, 1
    jz          update_enemy_vertical_action_end_pop
            pop         ax
    cmp         al, 1
    jz          update_enemy_vertical_action_end
    mov         al, 1
    call        update_enemy_horizontal_action
    jmp         update_enemy_vertical_action_end

    update_enemy_vertical_action_to_shoot:
    call        update_enemy_shoot_horizontal
    cmp         bl, 1
    jz          update_enemy_vertical_action_end_pop
            pop         ax
    cmp         al, 1
    jz          update_enemy_vertical_action_end
    mov         al, 1
    call        update_enemy_horizontal_action
    jmp         update_enemy_vertical_action_end

    update_enemy_vertical_action_end_pop:
    pop         ax
    update_enemy_vertical_action_end:
    pop         bx
    pop         ax
    ret
endp

check_if_enemy_alive proc; cx - enemy_index, bx - result
    push        ax
    push        dx
    push        cx

    call        get_enemy_pos
    mov         bx, ax

    mov         dx, cx
    inc dx
    mov         cx, enemies_count
    check_if_enemy_alive_loop:
        cmp         cx, dx
        jz          check_if_enemy_alive_skip
        push        cx
        dec cx
        call        get_enemy_pos
        cmp         ax, bx
        jz          check_if_enemy_alive_loop_matched
        jmp         check_if_enemy_alive_loop_did_not_match

        check_if_enemy_alive_loop_matched:
        call        get_enemy_status
        pop         cx
        cmp         al, status_dead
        jz          check_if_enemy_alive_skip
        cmp         al, status_dead_has_bullet
        jz          check_if_enemy_alive_skip
        jmp         check_if_enemy_alive_dead

        check_if_enemy_alive_loop_did_not_match:
        pop         cx
        check_if_enemy_alive_skip:
    loop check_if_enemy_alive_loop

    dec dx
    mov         cx, dx; cx - index
    call        get_enemy_tank_sprite
    mov         cx, ax; cx - desired sprite

    mov         ax, bx; ax - pos
    call        get_element_on_screen
    cmp         cx, dx
    jne check_if_enemy_alive_dead
    mov         bx, 1
    jmp         check_if_enemy_alive_end

    check_if_enemy_alive_dead:
    mov         bx, 0
    jmp         check_if_enemy_alive_end

    check_if_enemy_alive_end:
    pop         cx
    pop         dx
    pop         ax
    ret
endp

update_enemy_move_up proc; cx - enemy_index; output: bl - success flag
    push        cx
    push        di
    push        ax
    push        dx

    mov         di, cx
    call        get_enemy_pos
    mov         dx, ax; dx - old pos
    mov         bl, direction_up
    call        get_new_pos
    mov         cx, dx; cx - old pos, ax - new_pos
    call        get_element_on_screen
    cmp         dx, ground
    jz          update_enemy_move_up_fine
    cmp         dx, wall
    jz          update_enemy_move_up_shoot
    mov         bl, 0
    jmp         update_enemy_move_up_end

    update_enemy_move_up_shoot:
    mov         cx, di
    call        update_enemy_shoot_up
    jmp         update_enemy_move_up_end

    update_enemy_move_up_fine:
    push        ax
    mov         ax, cx
    call        erase
    pop         ax; ax - new_pos
    mov         cx, di; cx - enemy_index
    call        save_enemy_pos
    mov         al, direction_up
    call        store_enemy_direction
    mov         bl, 1
    jmp         update_enemy_move_up_end

    update_enemy_move_up_end:
    pop         dx
    pop         ax
    pop         di
    pop         cx
    ret
endp

update_enemy_move_down proc; cx - enemy_index; output: bl - success flag
    push        cx
    push        di
    push        ax
    push        dx

    mov         di, cx
    call        get_enemy_pos
    mov         dx, ax; dx - old pos
    mov         bl, direction_down
    call        get_new_pos
    mov         cx, dx; cx - old pos, ax - new_pos
    call        get_element_on_screen
    cmp         dx, ground
    jz          update_enemy_move_down_fine
    cmp         dx, wall
    jz          update_enemy_move_down_shoot
    mov         bl, 0
    jmp         update_enemy_move_down_end

    update_enemy_move_down_shoot:
    mov         cx, di
    call        update_enemy_shoot_down
    jmp         update_enemy_move_down_end

    update_enemy_move_down_fine:
    push        ax
    mov         ax, cx
    call        erase
    pop         ax; ax - new_pos
    mov         cx, di; cx - enemy_index
    call        save_enemy_pos
    mov         al, direction_down
    call        store_enemy_direction
    mov         bl, 1
    jmp         update_enemy_move_down_end

    update_enemy_move_down_end:
    pop         dx
    pop         ax
    pop         di
    pop         cx
    ret
endp

update_enemy_move_left proc; cx - enemy_index; output: bl - success flag
    push        cx
    push        di
    push        ax
    push        dx

    mov         di, cx
    call        get_enemy_pos
    mov         dx, ax; dx - old pos
    mov         bl, direction_left
    call        get_new_pos
    mov         cx, dx; cx - old pos, ax - new_pos
    call        get_element_on_screen
    cmp         dx, ground
    jz          update_enemy_move_left_fine
    cmp         dx, wall
    jz          update_enemy_move_left_shoot
    mov         bl, 0
    jmp         update_enemy_move_left_end

    update_enemy_move_left_shoot:
    mov         cx, di
    call        update_enemy_shoot_left
    jmp         update_enemy_move_left_end

    update_enemy_move_left_fine:
    push        ax
    mov         ax, cx
    call        erase
    pop         ax; ax - new_pos
    mov         cx, di; cx - enemy_index
    call        save_enemy_pos
    mov         al, direction_left
    call        store_enemy_direction
    mov         bl, 1
    jmp         update_enemy_move_left_end

    update_enemy_move_left_end:
    pop         dx
    pop         ax
    pop         di
    pop         cx
    ret
endp

update_enemy_move_right proc; cx - enemy_index; output: bl - success flag
    push        cx
    push        di
    push        ax
    push        dx

    mov         di, cx; di - enemy index
    call        get_enemy_pos
    mov         dx, ax; dx - old enemy pos
    mov         bl, direction_right
    call        get_new_pos
    mov         cx, dx; cx - old pos, ax - new_pos
    call        get_element_on_screen
    cmp         dx, ground
    jz          update_enemy_move_right_fine
    cmp         dx, wall
    jz          update_enemy_move_right_shoot
    mov         bl, 0
    jmp         update_enemy_move_right_end

    update_enemy_move_right_shoot:
    mov         cx, di
    call        update_enemy_shoot_right
    jmp         update_enemy_move_right_end

    update_enemy_move_right_fine:
    push        ax
    mov         ax, cx
    call        erase
    pop         ax; ax - new_pos
    mov         cx, di; cx - enemy_index
    call        save_enemy_pos
    mov         al, direction_right
    call        store_enemy_direction
    mov         bl, 1
    jmp         update_enemy_move_right_end

    update_enemy_move_right_end:
    pop         dx
    pop         ax
    pop         di
    pop         cx
    ret
endp

update_enemy_shoot_up proc; cx - enemy_index; output: bl - success flag
    push        ax

    call        get_enemy_status
    cmp         al, status_can_shoot
    jne update_enemy_shoot_up_fail

    call        get_enemy_pos
    call        erase
    call        set_enemy_bullet_pos
    mov         bl, direction_up
    call        set_enemy_bullet_direction
    mov         al, status_can_not_shoot
    call        store_enemy_status
    mov         al, direction_up
    call        store_enemy_direction

    inc cx
    call        update_enemy_bullet
    dec cx

    mov         bl, 1
    jmp         update_enemy_shoot_up_end

    update_enemy_shoot_up_fail:
    mov         bl, 0
    jmp         update_enemy_shoot_up_end

    update_enemy_shoot_up_end:
    pop         ax
    ret
endp

update_enemy_shoot_down proc; cx - enemy_index; output: bl - success flag
    push        ax

    call        get_enemy_status
    cmp         al, status_can_shoot
    jne update_enemy_shoot_down_fail

    call        get_enemy_pos
    call        erase
    call        set_enemy_bullet_pos
    mov         bl, direction_down
    call        set_enemy_bullet_direction
    mov         al, status_can_not_shoot
    call        store_enemy_status
    mov         al, direction_down
    call        store_enemy_direction

    inc cx
    call        update_enemy_bullet
    dec cx

    mov         bl, 1
    jmp         update_enemy_shoot_down_end

    update_enemy_shoot_down_fail:
    mov         bl, 0
    jmp         update_enemy_shoot_down_end

    update_enemy_shoot_down_end:
    pop         ax
    ret
endp

update_enemy_shoot_left proc; cx - enemy_index; output: bl - success flag
    push        ax

    call        get_enemy_status
    cmp         al, status_can_shoot
    jne update_enemy_shoot_left_fail

    call        get_enemy_pos
    call        erase
    call        set_enemy_bullet_pos
    mov         bl, direction_left
    call        set_enemy_bullet_direction
    mov         al, status_can_not_shoot
    call        store_enemy_status
    mov         al, direction_left
    call        store_enemy_direction

    inc cx
    call        update_enemy_bullet
    dec cx

    mov         bl, 1
    jmp         update_enemy_shoot_left_end

    update_enemy_shoot_left_fail:
    mov         bl, 0
    jmp         update_enemy_shoot_left_end

    update_enemy_shoot_left_end:
    pop         ax
    ret
endp

update_enemy_shoot_right proc; cx - enemy_index; output: bl - success flag
    push        ax

    call        get_enemy_status
    cmp         al, status_can_shoot
    jne update_enemy_shoot_right_fail

    call        get_enemy_pos
    call        erase
    call        set_enemy_bullet_pos
    mov         bl, direction_right
    call        set_enemy_bullet_direction
    mov         al, status_can_not_shoot
    call        store_enemy_status
    mov         al, direction_right
    call        store_enemy_direction

    inc cx
    call        update_enemy_bullet
    dec cx

    mov         bl, 1
    jmp         update_enemy_shoot_right_end

    update_enemy_shoot_right_fail:
    mov         bl, 0
    jmp         update_enemy_shoot_right_end

    update_enemy_shoot_right_end:
    pop         ax
    ret
endp

update_enemy_shoot_horizontal proc;cx - enemy_index; output: bl - success flag
    push        ax

    call        get_player_pos
    mov         bx, ax
    call        get_enemy_pos
    cmp         al, bl;al - enemy_x, bl - player_x
    jb update_enemy_shoot_horizontal_right

    call        update_enemy_shoot_left
    jmp         update_enemy_shoot_horizontal_end

    update_enemy_shoot_horizontal_right:
    call        update_enemy_shoot_right
    jmp         update_enemy_shoot_horizontal_end

    update_enemy_shoot_horizontal_end:
    pop         ax
    ret
endp

update_enemy_shoot_vertical proc;cx - enemy_index; output: bl - success flag
    push        ax
    call        get_player_pos
    mov         bx, ax
    call        get_enemy_pos
    cmp         ah, bh;ah - enemy_x, bh - player_x
    jb update_enemy_shoot_vertical_down

    call        update_enemy_shoot_up
    jmp         update_enemy_shoot_vertical_end

    update_enemy_shoot_vertical_down:
    call        update_enemy_shoot_down
    jmp         update_enemy_shoot_vertical_end

    update_enemy_shoot_vertical_end:
    pop         ax
    ret
endp

update_enemy_horizontal_action proc; cx - enemy_index, al - final_flag
    push        ax
    push        bx
    push        ax

    call        get_player_pos
    mov         bx, ax
    call        get_enemy_pos

    cmp         al, bl; bl - player, al - enemy
    jz          update_enemy_horizontal_action_to_shoot
    ja          update_enemy_horizontal_action_left
    jmp         update_enemy_horizontal_action_right

    update_enemy_horizontal_action_left:
    call        update_enemy_move_left
    cmp         bl, 1
    jz          update_enemy_horizontal_action_end_pop
    pop         ax
    cmp         al, 1
    jz          update_enemy_horizontal_action_end
    mov         al, 1
    call        update_enemy_vertical_action
    jmp         update_enemy_horizontal_action_end

    update_enemy_horizontal_action_right:
    call        update_enemy_move_right
    cmp         bl, 1
    jz          update_enemy_horizontal_action_end_pop
    pop         ax
    cmp         al, 1
    jz          update_enemy_horizontal_action_end
    mov         al, 1
    call        update_enemy_vertical_action
    jmp         update_enemy_horizontal_action_end

    update_enemy_horizontal_action_to_shoot:
    call        update_enemy_shoot_vertical
    cmp         bl, 1
    jz          update_enemy_horizontal_action_end_pop
    pop         ax
    cmp         al, 1
    jz          update_enemy_horizontal_action_end
    mov         al, 1
    call        update_enemy_vertical_action
    jmp         update_enemy_horizontal_action_end

    update_enemy_horizontal_action_end_pop:
    pop         ax
    update_enemy_horizontal_action_end:
    pop         bx
    pop         ax
    ret
endp

update_enemy_status_dead proc; cx - enemy_index
    push        ax

    call        get_enemy_status
    cmp         al, status_can_shoot
    jz          update_enemy_status_dead_has_no_bullet
    cmp         al, status_can_not_shoot
    jz          update_enemy_status_dead_has_bullet
    jmp         update_enemy_status_dead_end

    update_enemy_status_dead_has_bullet:
    mov         al, status_dead_has_bullet
    call        store_enemy_status
    jmp         update_enemy_status_dead_end

    update_enemy_status_dead_has_no_bullet:
    mov         al, status_dead
    call        store_enemy_status
    jmp         update_enemy_status_dead_end

    update_enemy_status_dead_end:
    call        get_enemy_pos
    call        erase
    pop         ax
    ret
endp

update_enemy proc; cx - enemy number
    push        cx
    push        ax
    push        bx

    dec cx; turn number to index

    call        get_enemy_status
    cmp         al, status_dead
    jz          update_enemy_dead_end
    cmp         al, status_dead_has_bullet
    jz          update_enemy_dead_end

    call        check_if_enemy_alive
    cmp         bx, 1
    jz          update_enemy_alive
    call        update_enemy_status_dead
    jmp         update_enemy_dead_end

    update_enemy_alive:

    call        get_distance_to_player
    cmp         ah, al
    ja          update_enemy_horizontal
    jmp         update_enemy_vertical

    update_enemy_vertical:
    mov         al, 0
    call        update_enemy_vertical_action
    jmp         update_enemy_end

    update_enemy_horizontal:
    mov         al, 0
    call        update_enemy_horizontal_action
    jmp         update_enemy_end


    update_enemy_end:
    call        draw_enemy
    update_enemy_dead_end:
    pop         bx
    pop         ax
    pop         cx
    ret
endp

update_enemies proc
    push        cx

    mov         cx, enemies_count
    update_enemies_loop:
        call        update_enemy
    loop update_enemies_loop

    update_enemies_end:
    pop         cx
    ret
endp

get_time_elapsed_since_start proc; cx:dx - result
    push        ax
    push        es

    mov         ax, 0
    mov         es, ax

    mov         cx, es:[46Ch]

    get_time_elapsed_since_start_end:
    pop         es
    pop         ax
    ret
endp

reset_counter proc
    push        cx
    push        dx
    push        ax

    mov         ax, 0
    mov         es, ax

    mov         word ptr es:[46Ch], 0

    reset_counter_end:
    pop         ax
    pop         dx
    pop         cx
    ret
endp

store_int proc; dx - value, di - pointer; output: di - new pointer
    push        ax
    push        dx
    push        bx

    mov         ax, dx
    store_int_loop:
        mov         dx, 0
        mov         bx, 10
        div         bx
        add         dx, '0'
        push        ax
        mov         ax, dx
        mov         ah, 07h
        stosw
        pop         ax
        cmp         ax, 0
        ja          store_int_loop


    store_int_end:
    pop         bx
    pop         dx
    pop         ax
    ret
endp

log_current_time proc
    push        cx
    push        dx
    push        ax
    push        di
    push        es
    push        bx

    mov         ax, ds
    mov         es, ax

    call        get_time_elapsed_since_start; cx:dx
    mov         ax, cx
    mov         bx, 40
    mul bx
    mov         bx, 12
    div         bx
    mov         bx, 60
    mov         dx, 0
    div         bx; ax - minutes, dx - seconds
    mov         dx, 0
    div         bx

    std

    mov         di, offset screen
    add         di, max_x * 2
    push        ax
    mov         ah, 07h
    mov         al, 's'
    stosw

    call        store_int

    mov         ah, 07h
    mov         al, ' '
    stosw
    mov         al, 'm'
    stosw

    pop         ax
    mov         dx, ax
    call        store_int

    mov         ax, empty
    mov         cx, 5
    rep         stosw

    cld

    log_current_time_end:
    pop         bx
    pop         es
    pop         di
    pop         ax
    pop         dx
    pop         cx
    ret
endp

victory proc
    push        ax
    push        es
    push        ds
    push        cx
    push        di
    push        si

    mov         ax, ds
    mov         es, ax
    mov         cx, screen_size
    mov         ax, green_screen
    mov         di, offset screen
    rep         stosw

    mov         cx, victory_word_size
    mov         ah, screen_heigth / 2
    mov         al, screen_width / 2
    sub         al, (victory_word_size / 2) + 1
    call        get_offset_on_screen
    mov         di, offset screen
    add         di, ax
    mov         si, offset victory_word
    rep         movsw

    call        update_screen
    victory_end:
    pop         si
    pop         di
    pop         cx
    pop         ds
    pop         es
    pop         ax
    ret
endp

fail proc
    push        ax
    push        es
    push        ds
    push        cx
    push        di
    push        si

    mov         ax, ds
    mov         es, ax
    mov         cx, screen_size
    mov         ax, red_screen
    mov         di, offset screen
    rep         stosw

    mov         cx, fail_word_size
    mov         ah, screen_heigth / 2
    mov         al, screen_width / 2
    sub         al, (fail_word_size / 2) + 1
    call        get_offset_on_screen
    mov         di, offset screen
    add         di, ax
    mov         si, offset fail_word
    rep         movsw

    call        update_screen
    fail_end:
    pop         si
    pop         di
    pop         cx
    pop         ds
    pop         es
    pop         ax
    ret
endp

game_loop proc
    call        reset_counter

    game_loop_loop:
        call        get_desired_action
        cmp         desired_action, exit
        jz          game_loop_end

        call        update_bullets

        call        update_player
        call        update_enemies

        call        log_current_time

        call        update_screen

        cmp         destroyed_base, 1
        jz          game_loop_victory

        cmp         player_killed, 1
        jz          game_loop_fail

        delay

    jmp         game_loop_loop

    game_loop_victory:
    call        victory
    long_delay
    jmp         game_loop_end

    game_loop_fail:
    call        fail
    long_delay
    jmp         game_loop_end

    game_loop_end:
    ret
endp

start:
    mov         ax, @data
    mov         ds, ax
    mov         es, ax

    call        set_video_mode

    call        init

    call        game_loop

    call        set_video_mode

start_end:
    mov         ax, 4C00h
    int         21h
end start