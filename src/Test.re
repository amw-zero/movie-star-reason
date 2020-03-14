open MovieStarReason;
open TestLib;

let testViewingMovies = () => {
  let state = {movies: [||], favoritedMovies: []};
  let state = Command.viewTopMovies(state);

  let expectedMovie = {title: "Wayne's World"};
  expect(expectedMovie.title, state.movies[0].title);
};

let testFavoritingMovies = () => {
  let title = "Movie 1"
  let state = {movies: [|{title: title}|], favoritedMovies: []};
  let state = Command.toggleFavoriteMovie(state.movies[0], state);


  expect(List.hd(state.favoritedMovies).title, title);
};

let tests = [
  {test: testViewingMovies, description: "Viewing Movies"},
  {test: testFavoritingMovies, description: "Favoriting Movies"}
];

runTests(tests);
