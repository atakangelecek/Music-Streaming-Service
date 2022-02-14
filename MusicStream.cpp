#include "MusicStream.h"

#include <iostream>

void MusicStream::addProfile(const std::string &email, const std::string &username, SubscriptionPlan plan) {
    Profile x(email,username, plan);
    profiles.insertAtTheEnd(x);
    /* TODO */
}

void MusicStream::deleteProfile(const std::string &email) {
    Node<Profile> *ptr = profiles.getFirstNode();
    int i=0;
    while(i<profiles.getSize()){
        if((ptr->data).getEmail() == email){
            break;
        }
        else{
            ptr = ptr->next;
        }
        i++;
    }
    // followersların followinginden beni siliyom
    Node<Profile*>* curr = (ptr->data).getFollowers().getFirstNode();
    do{
        curr->data->getFollowings().removeNode(&(ptr->data));
        curr = curr->next;
    }
    while(curr != (ptr->data).getFollowers().getFirstNode());
    
    //takip ettiklerimin takipçilerinden beni çıkra
    Node<Profile*>* curr2 = (ptr->data).getFollowings().getFirstNode();
    do{
        curr2->data->getFollowers().removeNode(&(ptr->data));
        curr2 = curr2->next;
    }
    while(curr2 != (ptr->data).getFollowings().getFirstNode());
    
    // playlistleri sil
    Node<Playlist> *temp = (ptr->data).getPlaylists().getFirstNode();
    do{
        (temp->data).getSongs().removeAllNodes();
        temp = temp->next;
    }
    while(temp != (ptr->data).getPlaylists().getFirstNode());

    (ptr->data).getPlaylists().removeAllNodes();
    // profiles linkedlistinden çıkardım
    profiles.removeNode(ptr);

}

void MusicStream::addArtist(const std::string &artistName) {
    
    Artist a(artistName);
    this->artists.insertAtTheEnd(a);
}

void MusicStream::addAlbum(const std::string &albumName, int artistId) {
    Album a(albumName);
    this->albums.insertAtTheEnd(a);

    Node<Artist> *ptr = artists.getFirstNode();
    do{
        if((ptr->data).getArtistId()  == artistId){
            break;
        }
        else{
            ptr = ptr->next;
        }
    }
    while(ptr != artists.getFirstNode());
     
    (ptr->data).addAlbum(&(albums.getLastNode()->data));
}

void MusicStream::addSong(const std::string &songName, int songDuration, int albumId) {
    Song a(songName,songDuration);
    this->songs.insertAtTheEnd(a);
    
    Node<Album> *ptr = albums.getFirstNode();
    do{
        if((ptr->data).getAlbumId() == albumId){
            break;
        }
        else{
            ptr = ptr->next;
        }
    }
    while(ptr != albums.getFirstNode());
    
    (ptr->data).addSong(&(songs.getLastNode()->data));
}

void MusicStream::followProfile(const std::string &email1, const std::string &email2) {
    
    Node<Profile> *ptr1 = this->profiles.getFirstNode();
    Node<Profile> *ptr2 = this->profiles.getFirstNode();
    do{
        if((ptr1->data).getEmail() == email1){
            break;
        }
        else{
            ptr1 = ptr1->next;
        }
    }
    while(ptr1 != this->profiles.getFirstNode());

    do{
        if((ptr2->data).getEmail() == email2){
            break;
        }
        else{
            ptr2 = ptr2->next;
        }
    }
    while(ptr2 != this->profiles.getFirstNode());
    Profile* a = &(ptr2->data);
    Profile* c = &(ptr1->data);
    (ptr1->data).followProfile(a);
    (ptr2->data).getFollowers().insertAtTheEnd(c);
}

void MusicStream::unfollowProfile(const std::string &email1, const std::string &email2) {
    Node<Profile> *ptr1 = this->profiles.getFirstNode();
    Node<Profile> *ptr2 = this->profiles.getFirstNode();
    do{
        if( (ptr1->data).getEmail() == email1 ){
            break;
        }
        else{
            ptr1 = ptr1->next;
        }
    }
    while(ptr1 != this->profiles.getFirstNode());

    
    do{
        if((ptr2->data).getEmail() == email2){
            break;
        }
        else{
            ptr2 = ptr2->next;
        }
    }
    while(ptr2 != this->profiles.getFirstNode());
    
    //Profile* a = &(ptr2->data);
    //Profile* c = &(ptr1->data);
    (ptr1->data).unfollowProfile( &(ptr2->data) );
    (ptr2->data).getFollowers().removeNode( &(ptr1->data) );
}

void MusicStream::createPlaylist(const std::string &email, const std::string &playlistName) {
    Node<Profile> *ptr1 = profiles.getFirstNode();
    do{
        if((ptr1->data).getEmail() == email){
            break;
        }
        else{
            ptr1 = ptr1->next;
        }
    }
    while(ptr1 != profiles.getFirstNode());
    
    (ptr1->data).createPlaylist(playlistName);
}

void MusicStream::deletePlaylist(const std::string &email, int playlistId) {
    Node<Profile> *ptr1 = profiles.getFirstNode();
    do{
        if((ptr1->data).getEmail() == email){
            break;
        }
        else{
            ptr1 = ptr1->next;
        }
    }
    while(ptr1 != profiles.getFirstNode());
    
    (ptr1->data).deletePlaylist(playlistId);
}

void MusicStream::addSongToPlaylist(const std::string &email, int songId, int playlistId) {
    Node<Profile> *ptr1 = profiles.getFirstNode();
    do{
        if((ptr1->data).getEmail() == email){
            break;
        }
        else{
            ptr1 = ptr1->next;
        }
    }
    while(ptr1 != profiles.getFirstNode());
    
    Node<Song> *curr = songs.getFirstNode();
    do{
        if((curr->data).getSongId() == songId){
            break;
        }
        else{
            curr = curr->next;
        }
    }
    while(curr != songs.getFirstNode());

    (ptr1->data).addSongToPlaylist(&(curr->data), playlistId);
}

void MusicStream::deleteSongFromPlaylist(const std::string &email, int songId, int playlistId) {
    Node<Profile> *ptr1 = profiles.getFirstNode();
    do{
        if((ptr1->data).getEmail() == email){
            break;
        }
        else{
            ptr1 = ptr1->next;
        }
    }
    while(ptr1 != profiles.getFirstNode());
    
    Node<Song> *curr = songs.getFirstNode();
    do{
        if((curr->data).getSongId() == songId){
            break;
        }
        else{
            curr = curr->next;
        }
    }
    while(curr != songs.getFirstNode());

    (ptr1->data).deleteSongFromPlaylist(&(curr->data), playlistId);
}

LinkedList<Song *> MusicStream::playPlaylist(const std::string &email, Playlist *playlist) {
    Node<Profile> *ptr1 = profiles.getFirstNode();
    do{
        if((ptr1->data).getEmail() == email){
            break;
        }
        else{
            ptr1 = ptr1->next;
        }
    }
    while(ptr1 != profiles.getFirstNode());

    if((ptr1->data).getPlan() == premium){
        return playlist->getSongs();
    }
    else{
        Node<Song*> *curr = playlist->getSongs().getFirstNode();
        Node<Song*> *temp;
        do{
            Song a("advertisement", 30);
            temp = new Node<Song*>(&a);
            temp->next = curr->next;
            curr->next->prev = temp;
            curr->next = temp;
            temp->prev = curr;
            curr = curr->next->next;     
        }
        while(curr != playlist->getSongs().getFirstNode());
        return playlist->getSongs();
    }
}

Playlist *MusicStream::getPlaylist(const std::string &email, int playlistId) {
    Node<Profile> *ptr1 = profiles.getFirstNode();
    do{
        if((ptr1->data).getEmail() == email){
            break;
        }
        else{
            ptr1 = ptr1->next;
        }
    }
    while(ptr1 != profiles.getFirstNode());

    return (ptr1->data).getPlaylist(playlistId);
}

LinkedList<Playlist *> MusicStream::getSharedPlaylists(const std::string &email) {
    Node<Profile> *ptr1 = profiles.getFirstNode();
    do{
        if((ptr1->data).getEmail() == email){
            break;
        }
        else{
            ptr1 = ptr1->next;
        }
    }
    while(ptr1 != profiles.getFirstNode());

    return ptr1->data.getSharedPlaylists();
}

void MusicStream::shufflePlaylist(const std::string &email, int playlistId, int seed) {
    Node<Profile> *ptr1 = profiles.getFirstNode();
    do{
        if((ptr1->data).getEmail() == email){
            break;
        }
        else{
            ptr1 = ptr1->next;
        }
    }
    while(ptr1 != profiles.getFirstNode());

    (ptr1->data).shufflePlaylist(playlistId, seed);
}

void MusicStream::sharePlaylist(const std::string &email, int playlistId) {
    Node<Profile> *ptr1 = profiles.getFirstNode();
    do{
        if((ptr1->data).getEmail() == email){
            break;
        }
        else{
            ptr1 = ptr1->next;
        }
    }
    while(ptr1 != profiles.getFirstNode());

    (ptr1->data).sharePlaylist(playlistId);
}

void MusicStream::unsharePlaylist(const std::string &email, int playlistId) {
    Node<Profile> *ptr1 = profiles.getFirstNode();
    do{
        if((ptr1->data).getEmail() == email){
            break;
        }
        else{
            ptr1 = ptr1->next;
        }
    }
    while(ptr1 != profiles.getFirstNode());

    (ptr1->data).unsharePlaylist(playlistId);
}

void MusicStream::subscribePremium(const std::string &email) {
    Node<Profile> *ptr1 = profiles.getFirstNode();
    do{
        if((ptr1->data).getEmail() == email){
            break;
        }
        else{
            ptr1 = ptr1->next;
        }
    }
    while(ptr1 != profiles.getFirstNode());
    (ptr1->data).setPlan(premium);
}

void MusicStream::unsubscribePremium(const std::string &email) {
    Node<Profile> *ptr1 = profiles.getFirstNode();
    do{
        if((ptr1->data).getEmail() == email){
            break;
        }
        else{
            ptr1 = ptr1->next;
        }
    }
    while(ptr1 != profiles.getFirstNode());
    (ptr1->data).setPlan(free_of_charge);
}

void MusicStream::print() const {
    std::cout << "# Printing the music stream ..." << std::endl;

    std::cout << "# Number of profiles is " << this->profiles.getSize() << ":" << std::endl;
    this->profiles.print();

    std::cout << "# Number of artists is " << this->artists.getSize() << ":" << std::endl;
    this->artists.print();

    std::cout << "# Number of albums is " << this->albums.getSize() << ":" << std::endl;
    this->albums.print();

    std::cout << "# Number of songs is " << this->songs.getSize() << ":" << std::endl;
    this->songs.print();

    std::cout << "# Printing is done." << std::endl;
}
